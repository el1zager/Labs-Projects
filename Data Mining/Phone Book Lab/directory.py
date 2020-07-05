import sqlite3

conn = sqlite3.connect("phone_book.db")
cursor = conn.cursor()

cursor.execute("""CREATE TABLE phone_book (name text, surname text, phone_number text, date_of_birth text)""")

cursor.execute("""INSERT INTO phone_book VALUES ('Elizaveta', 'Gerashchenko', '89200168652', '20.05.2000')""")

cursor.execute("""SELECT * FROM phone_book""")
while True:
    answer = cursor.fetchone()
    if answer is None:
        break
    else:
        print("{:<15} {:<20} {:<15} {:<15}".format(answer[0], answer[1], answer[2], answer[3]))
