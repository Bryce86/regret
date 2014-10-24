package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"os"
	"os/exec"
	"sort"
	"strconv"
	"strings"
	"time"
)

var logFile *os.File
var (
	//env     string
	//match   string
	command string
	proc    string
	logName string
	dirpath string
)

func init() {
	cfgFile, err := os.Open("./goconf.cfg")
	if err != nil {
		fmt.Println("read config file failed.")
		return
	}
	defer cfgFile.Close()

	br := bufio.NewReader(cfgFile)
	for {
		buff, _, err := br.ReadLine()
		if err != nil {
			if err == io.EOF {
				break
			}

			fmt.Println("ReadLine failed, " + err.Error())
			return
		}

		isSeparator := func(r rune) bool {
			return r == ':'
		}

		ss := strings.FieldsFunc(string(buff), isSeparator)

		if ss[0][0] == '"' {
			continue
		}
		fmt.Println(ss)

		switch ss[0] {
		case "proc":
			proc = ss[1]
			/*
			   case "env":
			   env = ss[1]

			   case "match":
			   match = ss[1]
			*/
		case "logName":
			logName = ss[1]
		case "cmd":
			command = ss[1]
		case "dirpath":
			dirpath = ss[1] + ":" + ss[2]

		default:
			fmt.Println("Invalid config parameter !")
			return
		}
	}

	if proc == "" || /* env == "" || match == "" || */ logName == "" || command == "" || dirpath == "" {
		fmt.Println("Parameters configured incomplete !")
		return
	}
	fmt.Println()
}

func WriteLogFile(format string, args ...interface{}) {
	if logFile != nil {
		fmt.Fprintf(logFile, time.Now().Format("2006-01-02 15:04:05")+" ")
		fmt.Fprintf(logFile, format, args...)
	}
}

func GetLogDir(searchDir string) string {
	// get dir infos
	fi, err := ioutil.ReadDir(searchDir)
	if err != nil {
		fmt.Println("read failed.")
		return ""
	}

	// get time
	t := strconv.Itoa(int(time.Now().Month())) + strconv.Itoa(time.Now().Day()) +
		strconv.Itoa(time.Now().Year()) + "_"
	//fmt.Println(t)

	// find current day dirs
	LogDirs := make(map[string]string)
	for i := 0; i < len(fi); i++ {
		if fi[i].IsDir() {
			if strings.Contains(fi[i].Name(), t) {
				key := strings.Index(fi[i].Name(), "_")
				LogDirs[fi[i].Name()[key+1:]] = fi[i].Name()
			}
		}
	}
	//fmt.Println(LogDirs)

	var keys []string
	for k := range LogDirs {
		keys = append(keys, k)
	}
	//fmt.Println(keys)
	sort.Strings(keys)
	return LogDirs[keys[len(keys)-1]]
}

func Server(port string) {
	lst, err := net.Listen("tcp", ":"+port)
	if err != nil {
		WriteLogFile("Listen failed: %s\n", err.Error())
		return
	}

	for {
		conn, err := lst.Accept()
		if err != nil {
			WriteLogFile("Accept fail: %s\n", err.Error())
			return
		} else {
			logFile, _ = os.OpenFile(logName, os.O_APPEND|os.O_RDWR|os.O_CREATE, 0777)
			defer logFile.Close()

			WriteLogFile("Welcome %s\n", conn.RemoteAddr().String())
			fmt.Printf("accept: %s\n", conn.RemoteAddr().String())
		}

		//goroutine
		go ExecProcess(conn)
	}
}

func ExecProcess(conn net.Conn) {
	buff := make([]byte, 1024)
	defer conn.Close()

	// recv
	n, err := conn.Read(buff)
	if err != nil {
		WriteLogFile("conn Read failed(%d): %s\n", n, err.Error())
		return
	}

	/*
		// env
		e := os.Getenv(env)
		if e == "" {
			WriteLogFile("Invalid Environment Variable %s", env)
			return
		}
	*/

	// process
	var Compress bool = false
	cmd := buff[:n]

	switch string(cmd[:2]) { // only
	case "go":

		/*
			if !strings.Contains(e, match) {
				WriteLogFile("Current E2010 Version isn't 1.60. No need to do this operation.\n")
				conn.Write([]byte("No Need."))
				return
			} else {
				fmt.Println("env: ", e)
			}
		*/

		var count, total int = 1, 1
		WriteLogFile("go to find process\n")
		for {
			c := exec.Command(command)
			d, err := c.Output()
			if err != nil {
				WriteLogFile("Output failed: %s\n", err.Error())
			}

			b := strings.Contains(string(d), proc)
			if b {
				fmt.Println("\nWaiting for Compressing ...")
				WriteLogFile("Waiting for Compressing ...\n")
				Compress = true
			} else {
				if Compress == true { // has Compress finished
					args := []string{"-f", "../CfgBootLdr.exe"}
					args = append(args, dirpath)
					WriteLogFile("exec.Command: %s %s\n", "cp", args)

					c := exec.Command("cp.exe", args...)
					err := c.Start()
					if err != nil {
						WriteLogFile("exec.Command: cp failed\n")
						fmt.Println("exec.Command: cp failed")
						return
					}

					fmt.Println("cp", args)
					Compress = false
					break
				} else {
					if count > total {
						fmt.Println()
						count = 1
						total++
					}

					fmt.Print(".")
					count++
				}
			}

			time.Sleep(5 * time.Second)
		}

		WriteLogFile("Construction Complete.\n")
		fmt.Println("\nConstruction Complete")
		conn.Write([]byte("Construction Complete"))

	case "cp":
		//WriteLogFile("copy SwUpgrade.log\n")

		// get log dir
		currpath := GetLogDir(dirpath)
		if currpath == "" {
			WriteLogFile("get log dir failed.\n")
			return
		}

		// write log dir
		_, err0 := conn.Write([]byte(currpath))
		if err0 != nil {
			WriteLogFile("write logDir failed.\n")
			return
		}

		// read log file
		file := dirpath + "\\" + currpath + "\\SwUpgrade.log"
		fmt.Println("get: ", file)
		WriteLogFile("get: %s\n", file)

		/*
			swLog, err := os.Open(file)
			if err != nil {
				WriteLogFile("Open SwUpgrade.log failed.\n")
				return
			}
			swLog.Close()

			br := bufio.NewReader(swLog)
			for {
				buff, err := br.ReadBytes('\n')
				if err != nil {
					if err == io.EOF {
						break
					}

					WriteLogFile("read SwUpgrade.log failed.\n")
					return
				}

				conn.Write(buff)
			}
		*/

		data, err := ioutil.ReadFile(file)
		if err != nil {
			WriteLogFile("read SwUpgrade.log failed.\n")
			return
		}
		conn.Write(data)

	default:
		WriteLogFile("Invalid command: %s\n", string(cmd))
		conn.Write([]byte("Invalid command"))
	}

	WriteLogFile("disconnect from %s\n\n", conn.RemoteAddr().String())
}

func main() {
	flag.Usage = func() {
		fmt.Printf("[Usage]\n\t\t%s port\n", os.Args[0])
	}
	flag.Parse()

	if flag.NArg() == 1 {
		Server(os.Args[1])
	} else {
		flag.Usage()
	}
}
