package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"math/rand"
	"net/http"
	"time"
	"os"
	"strconv"
)

func sendMessagesToBroker(pdType int) {
	brokerURL := "http://localhost:8080"
	i := 0
	for i < 1024*1024 {
		if i%1000 == 0 {
			fmt.Printf("Sending message %d...\n", i)
		}
		data := map[string]interface{}{
			"message_type":    pdType,
			"message_content": rand.Intn(1000) + 1,
		}

		// Convert data to JSON
		jsonData, err := json.Marshal(data)
		if err != nil {
			fmt.Printf("Error encoding JSON: %v\n", err)
			continue
		}

		// Send POST request with JSON data
		response, err := http.Post(brokerURL, "application/json", bytes.NewBuffer(jsonData))
		if err != nil {
			fmt.Printf("Error sending message: %v\n", err)
			time.Sleep(1 * time.Second)
			continue
		}
		if response.StatusCode == -520 {
			continue
		}
		i++
	}

	data := map[string]interface{}{
		"message_type":    pdType,
		"message_content": -1,
	}

	// Convert data to JSON
	jsonData, err := json.Marshal(data)
	if err != nil {
		fmt.Printf("Error encoding JSON: %v\n", err)
		return
	}

	// Send POST request with JSON data
	_, err = http.Post(brokerURL, "application/json", bytes.NewBuffer(jsonData))
	if err != nil {
		fmt.Printf("Error sending message: %v\n", err)
		time.Sleep(1 * time.Second)
	}
}

func main() {
	if len(os.Args) > 1 {
		arg, err := strconv.Atoi(os.Args[1])
		if err != nil {
			fmt.Println("Invalid argument provided. Should be a producer type: 1 or 2")
			return
		}
		sendMessagesToBroker(arg)
	} else {
		fmt.Println("No arguments provided. Should be provided producer type: 1 or 2")
	}
}