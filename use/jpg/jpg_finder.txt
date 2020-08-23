/*
* Author: James Spies, jspies2017@my.fit.edu
* Author: Stephen Brustowicz, sbrustowicz2018@my.fit.edu
* Course: CSE 4250, Spring 2020
* Project: proj1, Erased Images
* Implementation: go 1.13.6
*/

/*
* https://tour.golang.org/welcome/1 was a great resource for learning the basics of go
* https://golang.org/pkg/ helped figuring out how to use the imported packages
*/

package main

//Libraries
import (
	"fmt"
	"os"
	"net/http"
	"io"
	"strings"
	"bytes"
)

//all images are jpegs  "\xff\xd8\xff"

//Driver Function
func main(){

	//grab the url from command line argument
	fileURL := os.Args[1]

	//connect to url
	resp, err := http.Get(fileURL)
	
	//Check for erro reading URL
	if err != nil{
		panic(err)
	}
	
	//always close your files
	defer resp.Body.Close()
	
	//open the card.raw file
	infile, err := os.Open("card.raw")
	
	//check if it opened properly
	if err != nil{
		panic(err)
	}
	
	//always close your files
	defer infile.Close()

	var outfile *os.File
	
	//always close your files
	defer outfile.Close()
	
	//Declarations for breaking up the jpegs
	current := 1
	breakPoints := 512
	slices := make([]byte, breakPoints)
	
	//loop through each 512 byte chunk
	for{
		//read file chunk by chunk
		n, err := infile.Read(slices)
		
		//convert chunk to string for easier checking for jpeg header
		string_slice := bytes.NewBuffer(slices[:n]).String()
		
		//break out of the for loop if at the end of file
		
		if err == io.EOF{
			break
		}else{
			//find jpeg and write until new jpeg is found
			if strings.Contains(string_slice[0:3], "\xff\xd8\xff"){
				
				//create proper file name for new image, and use that proper name to write out
				ProperFileName := fmt.Sprintf("image%02d.jpg", current)
				outfile, _ = os.Create(ProperFileName)
				_, err := outfile.Write(slices[:n])
				
				//check for error is writing out
				if err != nil{
					panic(err)
				}
				
				//increment for new image
				current += 1
			}else{
				//while an outfile exists and we havent found a new jpeg header, keep writing to the same outfile
				if outfile != nil{
					_, err := outfile.Write(slices[:n])
					
					//check for error in writing out
					if err != nil{
						panic(err)
					}
				}
			}
		}
	}
}