1.1. Analysis of the Subject Area
Development of a system for automating reader services in a library, which will allow managing data about readers, books, and the process of lending and returning books. The system should provide convenient interaction between users and library resources, as well as take into account the need for multi-valued dependency and basic OOP (object-oriented principles).

1.1.1. Entities of the Subject Area:
1. Readers:
ID - unique identifier of the reader.
Name - full name of the reader.
Birthday - date of birth of the reader.
Email - email for communication.
Address - residential address of the reader.
Password - password for system access.

2. Books:
ID - unique identifier of the book.
Writer Name - name of the book's author.
Title - title of the book.
Publisher - publishing house.
Year of Publication - year of publication.
Total Copies - total number of copies.
Available Copies - number of copies available for lending.

3. Book Lending:
Reader ID - ID of the reader to whom the book is lent.
Book ID - ID of the book being lent.
Date of Lending - date when the book was lent.
Date of Return - date when the book should be returned.
