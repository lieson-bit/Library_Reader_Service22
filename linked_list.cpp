#include "linked_list.h"


bool isCompanyNumPresent(record* tail, const std::string& name) {
    if (!tail)
        return false;
    record* current = tail;
    while (current) {
        if (current->data.student_ID == name)
            return true;
        current = current->next;
    }
    return false;
}

bool addToBeginning(record** begin, Datatype elem, HashTable& myHashTable, Node*& root,std::string& file)
{
    bool isUserPresent = myHashTable.isUsernamePresent(elem.student_ID);
    bool present = searchByStringID(root, elem,file);
    if (isUserPresent && present ) {
        record* p = new record;
        p->data = elem;
        //myHashTable.add(elem.student_ID,elem.book_ID,1);
        //проверка, является ли список пустым
        if (*begin == NULL)
        {
            p->next = NULL;
        }
        else
        {
            p->next = *begin;
        }
        *begin = p;
        return true;
    } else {
        qDebug()<< "User with the specified username does not exist." << endl;
        return false;
    }

}

void DelElem(record** begin, record* ptrCur)
{
    record* p;
    if (ptrCur == *begin) {//удаляем первый элемент
        *begin = (*begin)->next;
    }
    else {
        p = *begin;
        while (p->next != ptrCur)
            p = p->next;
        // удаление элемента
        p->next = ptrCur->next;
    }
    delete ptrCur;
}

void Find_Element( record* tail, const std::string& k) {
    if (!tail) {
        qDebug()<< "Список пуст!";
        return;
    }
    record* p = tail;
    bool f = false;
    while (p != NULL) {
        if (p->data.student_ID == k) {
            f = true;
            //out << (p->data);
        }
        p = p->next;
    }
    if (!f) qDebug() << "Номер сотрудника не найден" << endl;
}

record* FindElemCompany(record* tail, const std::string& elem)
{
    if (tail == nullptr) {
        return nullptr;
    }
    record* p = tail;
    while (p != NULL) {
        if ((p->data.student_ID == elem))
            return p;
        p = p->next;
    }
    return nullptr;
}

void deleteByCompanyNum(record** tail, const std::string& name) {
    if (!tail) {
        std::cout << "Ссылка пуста" << std::endl;
        return;
    }
    record* ptr;
    ptr = FindElemCompany(*tail, name);
    if (ptr == NULL)qDebug()<< "Запись не найдена!" << endl;
    else { DelElem(tail, ptr); qDebug() << "Запись удалена!" << endl; };
}

record* editByCompanyNum(record* tail, const std::string& name, const Datatype& newData) {
    if (!tail) {
        return nullptr;
    }
    record* current = tail;
    while (current != NULL) {
        if (current->data.student_ID == name) {
            current->data = newData;
            return tail;
        }
        current = current->next;
    }
    return tail;
}

void downloadToFile(record* tail, const std::string& fileName) {
    if (!tail) {
        qDebug() << "Круговой связанный список пуст. Нечего скачивать." <<
            endl;
        return;
    }
    std::ofstream outFile(fileName);
    if (!outFile) {
        qDebug()<< "Failed to open file: " << QString::fromStdString(fileName) << endl;
        return;
    }
    record* current = tail;
    while (current != NULL) {
        outFile << std::setfill(' ') << current->data.student_ID << std::setw(8) <<
            " " << current->data.book_ID << " " << current->data.lending_date << std::setw(8)
            << " " << current->data.return_date << std::endl;
        current = current->next;
    };
    outFile.close();
    qDebug() << "Циклический связанный список, загруженный в файл: " << QString::fromStdString(fileName)<<
        endl;
}

void addToEnd(record** tail, const Datatype& data) {
    if (isCompanyNumPresent(*tail, data.student_ID)) {
        qDebug() << "Этот номер компании уже существует в списке" << endl;
        return;
    }
    record* new_record = new record();
    new_record->data = data;
    record* last = *tail;
    new_record->next = NULL;
    if (*tail == NULL) {
        *tail = new_record;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_record;
}

void copyDataFromFileToCircularList(const std::string& filename, record*& head) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    Datatype data;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        if (!(lineStream >> data.student_ID >> data.book_ID >> data.lending_date >>
            data.return_date))
        {
            std::cerr << "Неверные данные в файле. Пропуск строки." << std::endl;
            continue;
        }
        addToEnd(&head, data);
    }
    if (inputFile.eof()) {
        std::cout << "Дошел до конца файла." << std::endl;
    }
    else {
        std::cerr << "An error occurred while reading the file." << std::endl;
    }
    inputFile.close();
}

void free_All_record(record** begin) {
    if (*begin == 0) return;
    record* p = *begin;
    record* t;
    while (p)
    {
        t = p;
        p = p->next;
        delete t;
    }*begin = NULL;
}

record* merge(record* a, record* b) {
    // base case
    if (a == NULL) return b;
    if (b == NULL) return a;
    // рекурсивный случай, take a head pointer
    record* c;
    if (a->data.student_ID < b->data.student_ID) {
        c = a;
        c->next = merge(a->next, b);
    }
    else {
        c = b;
        c->next = merge(a, b->next);
    }
    return c;
}

record* mid_point(record* head) {
    // base case
    if (head == NULL || head->next == NULL) return head;
    // recursive case
    record* fast = head;
    record* slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next;
        if (fast->next == NULL)
            break;
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

record* merge_sort(record* head) {
    // base case
    if (head == NULL || head->next == NULL)
        return head;
    // recursive case
    // Step 1: divide the linked list into
    // two equal linked lists
    record* mid = mid_point(head);
    record* a = head;
    record* b = mid->next;
    mid->next = NULL;
    // Step 2: recursively sort the smaller
    // linked lists
    a = merge_sort(a);
    b = merge_sort(b);
    // Step 3: merge the sorted linked lists
    record* c = merge(a, b);
    return c;
}

