import re
import sqlite3
import datetime
from datetime import date

con = sqlite3.connect("phone_book.db")
cur = con.cursor()


def check_word_on_correctness(name_or_surname):
    arr = name_or_surname.split(" ")
    if len(arr) == 1:
        if name_or_surname.isalnum():
            if not re.match("^[A-Za-z0-9 ]*$", name_or_surname):
                print("Name or(and) Surname is not written in English")
                return -1
        else:
            print("Name or(and) Surname consists something else except letters, numbers and spaces")
            return -2
    else:
        for i in range(len(arr)):
            if arr[i].isalnum():
                if not re.match("^[A-Za-z0-9 ]*$", arr[i]):
                    print("Name or(and) Surname is not written in English")
                    return -1
            else:
                print("Name or(and) Surname consists something else except letters, numbers and spaces")
                return -2


def correct_word(name):
    name = name.capitalize()
    checking_name = check_word_on_correctness(name)
    while checking_name is not None:
        print("Incorrect name, try again")
        name = str(input())
        name = name.capitalize()
        checking_name = check_word_on_correctness(name)
    return name


def check_ns_on_repetition(name, surname):
    arr = [name, surname]
    cur.execute('SELECT * FROM phone_book WHERE name Like ? and surname Like ?', arr)
    ans = cur.fetchall()
    if len(ans) == 0:
        return True
    else:
        return False


def check_phone(phone):
    a = phone[0] + phone[1]
    if a == "+7":
        phone = phone.replace(a, "8")
        if not phone.isdigit() or len(phone) != 11:
            return -1
        else:
            return 1
    else:
        if phone[0] != '8' or not phone.isdigit() or len(phone) != 11:
            return -1
        else:
            return 0


def correct_phone(phone):
    checking_phone = check_phone(phone)
    if checking_phone == 1:
        phone = phone.replace("+7", "8")
    while checking_phone == -1:
        print("Incorrect phone number, try again")
        phone = str(input())
        checking_phone = check_phone(phone)
        if checking_phone == 1:
            phone = phone.replace("+7", "8")
    return phone


def check_date(date_name):
    array = date_name.split(".")
    y = int(array[2])
    m = int(array[1])
    d = int(array[0])
    try:
        date(y, m, d)
        date_now = datetime.date.today()
        date_of_birth = datetime.date(y, m, d)
        if date_now < date_of_birth:
            return False
        else:
            return True
    except:
        return False


def correct_date(user_date):
    checking_date = check_date(user_date)
    while not checking_date:
        print("Incorrect date. Try again")
        user_date = str(input())
        checking_date = check_date(user_date)
    return user_date


def show():
    cur.execute("""SELECT * FROM phone_book""")
    while True:
        answer = cur.fetchone()
        if answer is None:
            break
        else:
            print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
    start()


def search():
    print("In what way do you want to find info?")
    print("1. By name")
    print("2. By surname")
    print("3. By phone number")
    print("4. By date of birth")
    print("5. By name and surname")
    print("6. By name and phone number")
    print("7. By name and date of birth")
    print("8. By surname and phone number")
    print("9. By surname and date of birth")
    print("10. By phone number and date of birth")
    print("11. By name, surname and phone number")
    print("12. By name, surname and date of birth")
    print("13. By surname, phone number and date of birth")
    print("")
    print("Choose any number :)")
    print("P.S. If you don't receive info, it is only because there is no such user in phone book!")

    user_input = int(input())

    if user_input == 1:
        print("Enter the name")
        name = str(input())
        name = correct_word(name)
        cur.execute("""SELECT * FROM phone_book WHERE name Like ?""", [name])
        while True:
            answer = cur.fetchone()
            if answer is None:
                break
            else:
                print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
        start()

    elif user_input == 2:
        print("Enter the surname")
        surname = str(input())
        surname = correct_word(surname)
        cur.execute("""SELECT * FROM phone_book WHERE surname Like ?""", [surname])
        while True:
            answer = cur.fetchone()
            if answer is None:
                break
            else:
                print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
        start()

    elif user_input == 3:
        print("Enter the phone number")
        phone = str(input())
        phone = correct_phone(phone)

        cur.execute("""SELECT * FROM phone_book WHERE phone_number Like ?""", [phone])
        while True:
            answer = cur.fetchone()
            if answer is None:
                break
            else:
                print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
        start()

    elif user_input == 4:
        print("Enter date of birth")
        user_date = str(input())
        user_date = correct_date(user_date)

        cur.execute("""SELECT * FROM phone_book WHERE date_of_birth Like ?""", [user_date])
        while True:
            answer = cur.fetchone()
            if answer is None:
                break
            else:
                print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
        start()

    elif user_input == 5:
        print("Enter data this way: Name, Surname")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            name = arr[0]
            surname = arr[1]
            name = correct_word(name)
            surname = correct_word(surname)

            entry = [name, surname]
            cur.execute("""SELECT * FROM phone_book WHERE name Like ? and surname Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 6:
        print("Enter data this way: Name, phone number")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            name = arr[0]
            phone = arr[1]
            name = correct_word(name)
            phone = correct_phone(phone)

            entry = [name, phone]
            cur.execute("""SELECT * FROM phone_book WHERE name Like ? and phone_number Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 7:
        print("Enter data this way: Name, date of birth")

        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            name = arr[0]
            user_date = arr[1]
            name = correct_word(name)
            user_date = correct_date(user_date)

            entry = [name, user_date]
            cur.execute("""SELECT * FROM phone_book WHERE name Like ? and date_of_birth Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 8:
        print("Enter data this way: Surname, phone number")

        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            surname = arr[0]
            phone = arr[1]
            surname = correct_word(surname)
            phone = correct_phone(phone)

            entry = [surname, phone]
            cur.execute("""SELECT * FROM phone_book WHERE surname Like ? and phone_number Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 9:
        print("Enter data this way: Surname, date of birth")

        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            surname = arr[0]
            user_date = arr[1]
            surname = correct_word(surname)
            user_date = correct_date(user_date)

            entry = [surname, user_date]
            cur.execute("""SELECT * FROM phone_book WHERE surname Like ? and date_of_birth Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 10:
        print("Enter data this way: phone number, date of birth")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 2:
            print("Invalid number of arguments, try again")
            search()

        else:
            phone = arr[0]
            user_date = arr[1]
            phone = correct_phone(phone)
            user_date = correct_date(user_date)

            entry = [phone, user_date]
            cur.execute("""SELECT * FROM phone_book WHERE phone_number Like ? and date_of_birth Like ?""", entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 11:
        print("Enter data this way: Name, Surname, phone number")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 3:
            print("Invalid number of arguments, try again")
            search()

        else:
            name = arr[0]
            surname = arr[1]
            phone = arr[2]
            name = correct_word(name)
            surname = correct_word(surname)
            phone = correct_phone(phone)

            entry = [name, surname, phone]
            cur.execute("""SELECT * FROM phone_book WHERE name Like ? and surname Like ? and phone_number Like ?""",
                        entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 12:
        print("Enter data this way: Name, Surname, date of birth")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 3:
            print("Invalid number of arguments, try again")
            search()

        else:
            name = arr[0]
            surname = arr[1]
            user_date = arr[2]
            name = correct_word(name)
            surname = correct_word(surname)
            user_date = correct_date(user_date)

            entry = [name, surname, user_date]
            cur.execute("""SELECT * FROM phone_book WHERE name Like ? and surname Like ? and date_of_birth Like ?""",
                        entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    elif user_input == 13:
        print("Enter data this way: Surname, phone number, date of birth")
        user_input = str(input())

        arr = user_input.split(", ")
        if len(arr) != 3:
            print("Invalid number of arguments, try again")
            search()

        else:
            surname = arr[0]
            phone = arr[1]
            user_date = arr[2]
            surname = correct_word(surname)
            phone = correct_phone(phone)
            user_date = correct_date(user_date)

            entry = [surname, phone, user_date]
            cur.execute(
                """SELECT * FROM phone_book WHERE surname Like ? and phone_number Like ? and date_of_birth Like ?""",
                entry)
            while True:
                answer = cur.fetchone()
                if answer is None:
                    break
                else:
                    print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
            start()

    else:
        print("There is no such command, try again")
        search()


def add():
    print("Input data this way: Name, Surname, Phone Number, Date of birth (date is optional)")
    user_input = str(input())
    arr = user_input.split(", ")

    name = arr[0]
    surname = arr[1]
    phone = arr[2]
    if len(arr) == 4:
        user_date = arr[3]
        name = correct_word(name)
        surname = correct_word(surname)
        phone = correct_phone(phone)
        user_date = correct_date(user_date)

        if check_ns_on_repetition(name, surname):
            entry = [(name, surname, phone, user_date)]
            cur.executemany("INSERT INTO phone_book VALUES (?, ?, ?, ?)", entry)
            con.commit()
            start()

        else:
            print("Such combination of name and surname is already here, what are the next actions?")
            print("1. try again")
            print("2. change fields of this person")
            print("3. back to the main menu")
            user_input = str(input())
            if user_input == "1":
                add()
            if user_input == "2":
                change()
            if user_input == "3":
                start()
            else:
                print("There is no such command, try again")
                start()

    elif len(arr) == 3:
        name = correct_word(name)
        surname = correct_word(surname)
        phone = correct_phone(phone)

        arr.append("-")
        user_date = arr[3]

        if check_ns_on_repetition(name, surname):
            entry = [(name, surname, phone, user_date)]
            cur.executemany("INSERT INTO phone_book VALUES (?, ?, ?, ?)", entry)
            con.commit()
            start()

        else:
            print("Such combination of name and surname is already here, what are the next actions?")
            print("1. try again")
            print("2. change fields of this person")
            print("3. back to the main menu")
            user_input = str(input())
            if user_input == "1":
                add()
            if user_input == "2":
                change()
            if user_input == "3":
                start()
            else:
                print("There is no such command, try again")
                start()

    else:
        print("Invalid number of arguments, try again")
        add()


def delete():
    print("Write name and surname this way: Name, Surname")
    string = input()
    arr = string.split(", ")
    name = arr[0]
    surname = arr[1]

    name = correct_word(name)
    surname = correct_word(surname)

    delete_array = [name, surname]
    cur.executemany("""DELETE FROM phone_book WHERE name Like ? and surname Like ?""", [delete_array])
    con.commit()
    start()


def change():
    print("What do you want to change?")
    print("1. Name")
    print("2. Surname")
    print("3. Phone number")
    print("4. Date of birth")
    user_input = str(input())

    if user_input == "1":
        print("Please enter data this way: Name, Surname, New Name")
        user_input = str(input())
        user_array = user_input.split(", ")
        if len(user_array) == 3:
            name_new = user_array[2]
            name_old = user_array[0]
            surname = user_array[1]

            name_old = correct_word(name_old)
            surname = correct_word(surname)

            if check_ns_on_repetition(name_old, surname):
                print("There is no such person, want to try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = str(input())
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()

            name_new = correct_word(name_new)

            if check_ns_on_repetition(name_new, surname):
                arr = [name_new, name_old, surname]
                cur.execute("""UPDATE phone_book SET name = ? WHERE name = ? and surname = ?""", arr)
                con.commit()
                start()

            else:
                print("Such combination of name and surname is already here. Try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = input()
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()

        else:
            print("Invalid number of arguments, required 3. Try again")
            print("")
            change()

    if user_input == "2":
        print("Please enter data this way: Name, Surname, New Surname")
        user_input = str(input())
        user_array = user_input.split(", ")
        if len(user_array) == 3:
            surname_new = user_array[2]
            name = user_array[0]
            surname_old = user_array[1]

            surname_old = correct_word(surname_old)
            name = correct_word(name)

            if check_ns_on_repetition(name, surname_old):
                print("There is no such person, want to try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = str(input())
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

            surname_new = correct_word(surname_new)

            if check_ns_on_repetition(name, surname_new):
                arr = [surname_new, name, surname_old]
                cur.execute("""UPDATE phone_book SET surname = ? WHERE name = ? and surname = ?""", arr)
                con.commit()
                start()

            else:
                print("Such combination of name and surname is already here. Try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = input()
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

        else:
            print("Invalid number of arguments, required 3. Try again")
            print("")
            change()

    if user_input == "3":
        print("Please enter data this way: Name, Surname, New Phone number")
        user_input = str(input())
        user_array = user_input.split(", ")
        if len(user_array) == 3:
            phone = user_array[2]
            name = user_array[0]
            surname = user_array[1]

            name = correct_word(name)
            surname = correct_word(surname)

            if check_ns_on_repetition(name, surname):
                print("There is no such person, want to try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = str(input())
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

            phone = correct_phone(phone)

            if check_ns_on_repetition(name, surname):
                arr = [phone, name, surname]
                cur.execute("""UPDATE phone_book SET phone_number = ? WHERE name = ? and surname = ?""", arr)
                con.commit()
                start()

            else:
                print("Such combination of name and surname is already here. Try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = input()
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

        else:
            print("Invalid number of arguments, required 3. Try again")
            print("")
            change()

    if user_input == "4":
        print("Please enter data this way: Name, Surname, New Date of birth")
        user_input = str(input())
        user_array = user_input.split(", ")
        if len(user_array) == 3:
            user_date = user_array[2]
            name = user_array[0]
            surname = user_array[1]

            name = correct_word(name)
            surname = correct_word(surname)

            if check_ns_on_repetition(name, surname):
                print("There is no such person, want to try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = str(input())
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

            user_date = correct_date(user_date)

            if check_ns_on_repetition(name, surname):
                arr = [user_date, name, surname]
                cur.execute("""UPDATE phone_book SET date_of_birth = ? WHERE name = ? and surname = ?""", arr)
                con.commit()
                start()

            else:
                print("Such combination of name and surname is already here. Try again?")
                print("1. Try again")
                print("2. Back to the main menu")
                user_input = input()
                if user_input == "1":
                    change()
                if user_input == "2":
                    start()
                else:
                    print("There is no such command, try again")
                    start()

        else:
            print("Invalid number of arguments, required 3. Try again")
            print("")
            change()


def find_age():
    print("Write name and surname this way: Name, Surname")
    string = input()
    arr = string.split(", ")

    if len(arr) == 2:
        name = arr[0]
        surname = arr[1]

        name = correct_word(name)
        surname = correct_word(surname)

        if check_ns_on_repetition(name, surname):
            print("There is no such person, want to try again?")
            print("1. Try again")
            print("2. Back to the main menu")
            user_input = str(input())
            if user_input == "1":
                find_age()
            if user_input == "2":
                start()
            else:
                print("There is no such command, try again")
                start()

        search_array = [name, surname]
        cur.execute("""SELECT date_of_birth FROM phone_book WHERE name Like ? and surname Like ?""", search_array)
        ans = cur.fetchone()

        person_date = ans[0]
        person_array = person_date.split(".")
        d = int(person_array[0])
        m = int(person_array[1])
        y = int(person_array[2])
        date_now = datetime.date.today()
        date_of_birth = datetime.date(y, m, d)
        time = date_now - date_of_birth
        age = int(time.days / 365)
        print(age)

        start()

    else:
        print("Invalid number of arguments, try again")
        find_age()


def quit():
    print("Thank you for using my phone book. Bye!")
    con.close()


def start():
    print("List of commands:")
    print("1. view all phone book entries")
    print("2. phone book search")
    print("3. adding a new entry")
    print("4. delete an entry by name and surname")
    print("5. change any field in any entry")
    print("6. display the age of a person by name and surname")
    print("7. quit")
    print(" ")
    print("Choose any command number :)")

    u_input = str(input())
    if u_input == "1":
        show()
    elif u_input == "2":
        search()
    elif u_input == "3":
        add()
    elif u_input == "4":
        delete()
    elif u_input == "5":
        change()
    elif u_input == "6":
        find_age()
    elif u_input == "7":
        quit()

    else:
        print("There is no such command, try again")
        start()


print("Welcome to my phone book! I hope you will enjoy it")
start()
