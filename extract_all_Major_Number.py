#DATE: 1 JAN 2018
#AMAR SINGH
#UBUNTU (LINUX)
#Tells the number of Char and Block drivers are there on system
#Also extracts all the Major Numbers in use by parsing "ls -al" output
#And if a number is passed then it tells the availability of it for a major number

import os  
import sys

# editing and removing directories and links  from "ls -al" command output
os.system("ls -al /dev > ls.txt")#lists all the device file
fp1 = open("ls.txt","r")
fp2 = open("edited.txt","w")

num_of_char = 0 #to hold number of Char drivers
num_of_block = 0 #to hold number of Block drivers
for line in fp1:
	if(line[0] == 'l' or line[0] == 'd'):
		continue #deleting the lines for directory and links in ls.txt
	else:
		if(line[0]=='c'):
			num_of_char +=1
		elif(line[0]=='b'):
			num_of_block +=1
		fp2.write(line)

fp2.close()
fp1.close()

print "Number of CHAR DRIVER: "+str(num_of_char)
print "Number of BLOCK DRIVER: "+str(num_of_block) 

#extracting the major number with the help of comma(',') present just after it

fp1 = open("edited.txt","r")

number = 0;#major number
mn = [0,256]#to store the major numbers

#function to store the major number extracted, in a sorted way

def store(numb,mn):

	for i in mn:
		if(i==numb):
			return mn
		elif(i<numb):
			continue
		else:
			mn.insert(mn.index(i),numb)
			return mn
	mn.append(numb)
	return mn

#function ends here

for line in fp1:
	line = line.split(" ") 
	for word in line:
		if((len(word) >1) and word[-1] == ','):
			#print (word, len(word)) #debug
			
			if(len(word)==2):
				number = int(word[0])
				break
			elif(len(word)==3):
				number = (int(word[0])*10)+(int(word[1]))
				break
			elif(len(word)==4):
				number = (int(word[0])*100)+(int(word[1])*10)+(int(word[2]))
				break				
		
	mn = store(number,mn)
print "List of Major Numbers in use: "	
print mn
fp1.close()



#checking if the passed number is available for major number
if( len(sys.argv) > 1):
	if(int(sys.argv[1]) in mn):
		print "\n"+sys.argv[1]+' is not available'
	else:		
		print "\n"+sys.argv[1]+' is available'


#cleaning the system 
os.system("rm ls.txt edited.txt")
print 'Thank You'
