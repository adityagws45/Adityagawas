#!/bin/bash
# Name: Aditya Gawas
# Batch: T1
# Roll No: 17
# Class: TEIT
# Assignment No: 1

echo -e "Address Book\n"

echo -e "Enter file name:"
read fname

# Check if the file already exists; if not, create it and add header
if [ ! -f "$fname" ]; then
    touch "$fname"
    echo -e "id \t name \t mobile_no \t salary \t location" > "$fname"
fi

ch=0
while [ "$ch" -lt 7 ]
do
    echo -e "\n1) Create Address Book"
    echo -e "2) View Address Book"
    echo -e "3) Insert a Record"
    echo -e "4) Delete a Record"
    echo -e "5) Modify a Record"
    echo -e "6) Search a Record"
    echo -e "7) Exit"
    
    echo -e "\nEnter Your Choice:"
    read ch

    case $ch in 
        1)
            echo "Enter number of records:"
            read n
            for((i=0; i<n; i++))
            do
                echo "Enter id:"
                read id
                echo "Enter name:"
                read name
                echo "Enter mobile number:"
                read mno
                echo "Enter salary:"
                read sal
                echo "Enter location:"
                read loc
                echo -e "$id \t $name \t $mno \t $sal \t $loc" >> "$fname"
            done
        ;;

        2)
            cat "$fname"
        ;;

        3) 
            echo "Enter id:"
            read id
            echo "Enter name:"
            read name
            echo "Enter mobile number:"
            read mno
            echo "Enter salary:"
            read sal
            echo "Enter location:"
            read loc
            echo -e "$id \t $name \t $mno \t $sal \t $loc" >> "$fname"  
        ;;

        4)
            echo "Enter Employee ID to delete:"
            read id
            if grep -w "$id" "$fname" > /dev/null
            then
                grep -wv "$id" "$fname" > temp && mv temp "$fname"
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
        ;;

        5)
            echo "Enter Employee ID to modify:"
            read id
            if grep -w "$id" "$fname" > /dev/null
            then
                grep -wv "$id" "$fname" > temp && mv temp "$fname"
                
                echo "Enter new id:"
                read id
                echo "Enter name:"
                read name
                echo "Enter mobile number:"
                read mno
                echo "Enter salary:"
                read sal
                echo "Enter location:"
                read loc
                echo -e "$id \t $name \t $mno \t $sal \t $loc" >> "$fname"
                echo "Record modified successfully."
            else
                echo "Record not found."
            fi
        ;;

        6)
            echo "Enter Employee ID to search:"
            read id
            if grep -w "$id" "$fname" > /dev/null
            then
                echo "Record found:"
                grep -w "$id" "$fname"
            else
                echo "Record not found."
            fi
        ;;

        7)
            echo "Exiting the program."
        ;;

        *)
            echo "Invalid choice. Please try again."
        ;;
    esac
done
adityagawas@adityagawas-VirtualBox:~$ ./program1.sh
bash: ./program1.sh: No such file or directory
adityagawas@adityagawas-VirtualBox:~$ ./progrm1.sh
bash: ./progrm1.sh: Permission denied
adityagawas@adityagawas-VirtualBox:~$ chmod 754 progrm1.sh
adityagawas@adityagawas-VirtualBox:~$ Address Book
Address: command not found
adityagawas@adityagawas-VirtualBox:~$  ./program.sh
bash: ./program.sh: Permission denied
adityagawas@adityagawas-VirtualBox:~$ chmod 754 program.sh
adityagawas@adityagawas-VirtualBox:~$ Address Book\n
Address: command not found
adityagawas@adityagawas-VirtualBox:~$ ls
 Desktop     Music               program.sh   shell1      shell5.sh   Templates
 dir         myfile              progrm1.sh   shell2.sh   shell6.sh   Videos
 Documents  'New Document.txt'   Public       shell3.sh   shell7.sh
 Downloads   Pictures            shell        shell4.sh   snap
adityagawas@adityagawas-VirtualBox:~$ chmod +x program.sh
adityagawas@adityagawas-VirtualBox:~$ ./program.sh
Address Book

Enter file name:
myaddress

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
1
Enter number of records:
2
Enter id:
01
Enter name:
shiv
Enter mobile number:
3434r
Enter salary:
23233r
Enter location:
pune
Enter id:
04
Enter name:
3423
Enter mobile number:
343
Enter salary:
32323
Enter location:
adityanagar

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
2
id 	 name 	 mobile_no 	 salary 	 location
01 	 shiv 	 3434r 	 23233r 	 pune
04 	 3423 	 343 	 32323 	 adityanagar

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
4
Enter Employee ID to delete:
01
Record deleted successfully.

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
2
id 	 name 	 mobile_no 	 salary 	 location
04 	 3423 	 343 	 32323 	 adityanagar

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
5
Enter Employee ID to modify:
02
Record not found.

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
5
Enter Employee ID to modify:
01
Record not found.

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
6
Enter Employee ID to search:
1
Record not found.

1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
6) Search a Record
7) Exit

Enter Your Choice:
7
Exiting the program.
adityagawas@adityagawas-VirtualBox:~$ 

