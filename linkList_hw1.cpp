// Homework #2, Jordan Paul

#include <iostream>
#include <string.h>

// ==================================================================
// Data class. used to either store int or char and handles
//             printing of it's data type and comparison of
//             it's data types
// ==================================================================

class Data{
private:
    enum{INT, CHAR} type;

public:
    char    inChar;
    int     inInt;

    Data(int inValue): inInt(inValue), type(INT) {}
    Data(char inValue): inChar(inValue), type(CHAR) {}

    friend std::ostream& operator << (std::ostream& os, const Data& data){
        if (data.type == INT) os << data.inInt;
        else os << data.inChar;
        return os;
    }

    bool operator==(const Data& other) const {
        if (other.type != type) return false;
        return type == INT ? inInt == other.inInt : inChar == other.inChar;
    }
};

// ==================================================================
// Single Link List     Single Link List    Single Link List
// Single Link List     Single Link List    Single Link List
// ==================================================================

template<class T>
class SLLNode {
public:
    SLLNode(): next(0) {}

    SLLNode(T el, SLLNode *ptr = 0): info(el), next(ptr) {}

    T info;
    SLLNode *next;
};

template<class T>
class SingleLinkList{
public:
    SingleLinkList() { head = tail = 0; }
    ~SingleLinkList(){
        for (SLLNode<T> *p; !isEmpty();){
            p = head->next;
            delete head;;
            head = p;
        }
    };

    bool isEmpty() { return head == 0; }

    void addToHead(const T& el){
        SLLNode<T> *tmp = new SLLNode<T>(el);
        tmp->next = head;
        head = tmp;
        if(tail == 0) tail = head;
    }

    void addToTail(const T& el){
        if (tail != 0) {
            tail->next = new SLLNode<T>(el);
            tail = tail->next;
        }else head = tail = new SLLNode<T>(el);
    }

    T deleteFromHead(){
        T el = head->info;
        SLLNode<T> *tmp = head;
        if (head == tail) head = tail = 0;
        else head = head->next;
        delete tmp;
        return el;
    }

    T deleteFromTail() {
        T el = tail->info;
        if (head == tail) {   // if only one node on the list;
            delete head;
            head = tail = 0;
        }
        else {                // if more than one node in the list,
            SLLNode<T> *tmp; // find the predecessor of tail;
            for (tmp = head; tmp->next != tail; tmp = tmp->next);
            delete tail;
            tail = tmp;      // the predecessor of tail becomes tail;
            tail->next = 0;
        }
        return el;
    }

    void deleteNode(const T& el) {
        if (head != 0) {                   // if non-empty list;
            if (head == tail && el == head->info) { // if only one
                delete head;                       // node on the list;
                head = tail = 0;
            } else if (el == head->info) {  // if more than one node on the list
                SLLNode<T> *tmp = head;
                head = head->next;
                delete tmp;              // and old head is deleted;
            } else {                        // if more than one node in the list
                SLLNode<T> *pred, *tmp;
                for (pred = head, tmp = head->next; // and a non-head node
                     tmp != 0 && !(tmp->info == el);// is deleted;
                     pred = pred->next, tmp = tmp->next);
                if (tmp != 0) {
                    pred->next = tmp->next;
                    if (tmp == tail)
                        tail = pred;
                    delete tmp;
                }
            }
        }
    }

    bool isInList(const T& el) const {
        SLLNode<T> *tmp;
        for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
        return tmp != 0;
    }

    void printAll() const {
        for (SLLNode<T> *tmp = head; tmp != 0; tmp = tmp->next)
            std::cout << tmp->info << " ";
        std::cout << std::endl;
    }

    void clear() {
        for (SLLNode<T> *tmp; head != 0; ) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

private:
    SLLNode<T> *head, *tail;

};

// ==================================================================
// Double Link List     Double Link List    Double Link List
// Double Link List     Double Link List    Double Link List
// ==================================================================

template<class T>
class DLLNode {
public:
    DLLNode(): next(0), prev(0) {}
    DLLNode(T el, DLLNode *n = 0, DLLNode *p = 0): info(el), next(n), prev(p) {}

    T info;
    DLLNode *next, *prev;
};

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head = tail = 0;
    }
    void addToDLLTail(const T&);
    T deleteFromDLLTail();
    ~DoublyLinkedList() { clear(); }
    bool isEmpty() const { return head == 0; }
    void clear();
    void setToNull() { head = tail = 0; }
    void addToDLLHead(const T&);
    T deleteFromDLLHead();
    void deleteNode(const T&);
    T& firstEl();
    T* find(const T&) const;
    bool isInList(const T&);
    void printAll() { for (DLLNode<T> *tmp = head; tmp != 0;
        tmp = tmp->next) { std::cout << tmp->info << " "; } std::cout << std::endl;}
protected:
    DLLNode<T> *head, *tail;
};

template<class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el) {
    if (head != 0) {
        head = new DLLNode<T>(el, head, 0);
        head->next->prev = head;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el) {
    if (tail != 0) {
        tail = new DLLNode<T>(el,0,tail);
        tail->prev->next = tail;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLHead() {
    T el = head->info;
    if (head == tail) { // if only one DLLNode on the list;
        delete head;
        head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
        head = head->next;
        delete head->prev;
        head->prev = 0;
    }
    return el;
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLTail() {
    T el = tail->info;
    if (head == tail) { // if only one DLLNode on the list;
        delete head;
        head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
        tail = tail->prev;
        delete tail->next;
        tail->next = 0;
    }
    return el;
}

template<class T>
void DoublyLinkedList<T>::deleteNode(const T& el){
    if (!isInList(el)) return;

    if (el == head->info) {
        //std::cout << "deleting head: " << el << std::endl;
        deleteFromDLLHead();
    }else if(el == tail->info){
        //std::cout << "deleting tail: " << el << std::endl;
        deleteFromDLLTail();
    }else{
        //std::cout << "deleting middle: " << el << std::endl;
        DLLNode<T> *pred, *tmp;
        for (pred = head, tmp = head->next; // and a non-head node
             tmp != 0 && !(tmp->info == el);// is deleted;
             pred = pred->next, tmp = tmp->next);

        if (tmp != 0) {
            pred->next = tmp->next;
            tmp->prev = pred;

            if (tmp->next != 0){
                tmp->next->prev = pred;
            }

            if (tmp == tail) tail = pred;
            delete tmp;
        }
    }
}

template<class T>
bool DoublyLinkedList<T>::isInList(const T& el) {
    DLLNode<T> *tmp = head;
    for ( ; tmp != 0 && !(tmp->info == el);  // overloaded ==
            tmp = tmp->next);
    return tmp != 0;
}

template <class T>
T* DoublyLinkedList<T>::find(const T& el) const {
    DLLNode<T> *tmp = head;
    for ( ; tmp != 0 && !(tmp->info == el);  // overloaded ==
            tmp = tmp->next);
    if (tmp == 0)
        return 0;
    else return &tmp->info;
}

template<class T>
T& DoublyLinkedList<T>::firstEl() {
    return head->info;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    for (DLLNode<T> *tmp; head != 0; ) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ==================================================================
// Main Function    Main Function   Main Function   Main Function
// Main Function    Main Function   Main Function   Main Function
// ==================================================================

void printMenu(){
    std::cout << std::endl << "                  == MENU ==" << std::endl;
    std::cout << "SLL: IH(0), IT(1), DH(2), DT(3), SD(4),  PS(5)" << std::endl;
    std::cout << "DLL: IH(6), IT(7), DH(8), DT(9), SD(10), PD(11)" << std::endl;
    std::cout << "Exit Program (12)" << std::endl << std::endl;
    std::cout << "Choose:   ";
}

void getOperation(int &inInt, char &inChar){
    std::cin >> inInt;
    if (!std::cin){
        std::cin.clear();
        std::cin >> inChar;
        inInt = -1;
    }
}

void constructData(Data *&data){
    int inInt;
    char inChar;

    getOperation(inInt, inChar);

    if (inInt != -1) data = new Data(inInt);
    else data = new Data(inChar);
}

void emptyList() { std::cout << "Error: list is empty" << std::endl; }
void notFound() { std::cout << "Error: Element not in list" << std::endl; }

// ==================================================================
// Single Link list Test        Single Link list Test
// Single Link list Test        Single Link list Test
// ==================================================================

int sllIsEmpty(SingleLinkList<Data> *sll){
    if (!sll->isEmpty()) {
        std::cout << "Expected the Single Link list to be empty" << std::endl;
        return 0;
    }
    std::cout << "Single Link list elements successfully removed" << std::endl;
    return 1;
}

int sllInsertRemoveHead(SingleLinkList<Data> *sll){
    std::cout << "\nInserting set {0...9} at head" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        sll->addToHead(i);
    }

    std::cout << "Removing and testing elements from head: list contents = ";
    sll->printAll();

    count = 9;
    while (!sll->isEmpty()){
        popped = sll->deleteFromHead().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count--;
    }

    std::cout << "Insert and removed from head test passed" << std::endl;
    return 1;
}

int sllInsertHeadRemoveTail(SingleLinkList<Data> *sll){

    std::cout << "\nInserting set {0...9} at head" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        sll->addToHead(i);
    }

    std::cout << "-Removing and testing elements from tail: list contents = ";
    sll->printAll();

    count = 0;
    while (!sll->isEmpty()){
        popped = sll->deleteFromTail().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count++;
    }

    std::cout << "Insert at head and removed from tail test passed" << std::endl;
    return 1;
}

int sllInsertRemoveTail(SingleLinkList<Data> *sll){

    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        sll->addToTail(i);
    }

    std::cout << "-Removing and testing elements from tail: list contents = ";
    sll->printAll();

    count = 9;
    while (!sll->isEmpty()){
        popped = sll->deleteFromTail().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count--;
    }

    std::cout << "Insert at tail and removed from tail test passed" << std::endl;
    return 1;
}

int sllInsertTailRemoveHead(SingleLinkList<Data> *sll){

    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        sll->addToTail(i);
    }

    std::cout << "-Removing and testing elements from head: List contents = ";
    sll->printAll();

    count = 0;
    while (!sll->isEmpty()){
        popped = sll->deleteFromHead().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count++;
    }

    std::cout << "Insert at tail and removed head test passed" << std::endl;
    return 1;
}

int sllInsertTailRemoveEvenOdds(SingleLinkList<Data> *sll){
    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;

    for (int i = 0; i < 10; i++){
        sll->addToTail(i);
    }

    std::cout << "-Removing even numbers from list: List contents = ";
    sll->printAll();

    for (int i = 0; i < 10; i+=2) { sll->deleteNode(i); }
    for (int i = 0; i < 10; i+=2) {
        if (sll->isInList(i)){
            std::cout << "Expected " << i << " to not be in list" << std::endl;
            return 0;
        }
    }

    std::cout << "list contents after removal: ";
    sll->printAll();

    std::cout << "-Removing Odd numbers from list" << std::endl;
    for (int i = 0; i < 10; i+=2) { sll->deleteNode(i + 1); }
    for (int i = 0; i < 10; i+=2) {
        if (sll->isInList(i + 1)){
            std::cout << "Expected " << i + 1 << " to not be in list" << std::endl;
            return 0;
        }
    }

    std::cout << "Insert at tail and removed Even and Odds from head test passed" << std::endl;
    return 1;
}

int sllCharacterTest(SingleLinkList<Data> *sll){
    std::cout << "\nCharacter Insert and delete test: Inserting hello, world into list" << std::endl;

    char hello_world[13] = {'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'};

    for (int i = 0; i < 13; i++){
        sll->addToTail(hello_world[i]);
    }

    std::cout << "Single Link list Contents: ";
    sll->printAll();

    for (int i = 0; i < 13; i++){
        char chr = sll->deleteFromHead().inChar;
        if (chr != hello_world[i]){
            std::cout << "Expected character on head remove: " << hello_world[i] << std::endl;
            return 0;
        }
    }

    std::cout << "Insert character string: 'Hello, world' and removed passed" << std::endl;

    return 1;
}

// ==================================================================
// Double Link list Test        Double Link list Test
// Double Link list Test        Double Link list Test
// ==================================================================

int dllIsEmpty(DoublyLinkedList<Data> *dll){
    if (!dll->isEmpty()) {
        std::cout << "Expected the Double Link list to be empty" << std::endl;
        return 0;
    }
    std::cout << "Double Link list elements successfully removed" << std::endl;
    return 1;
}

int dllInsertRemoveHead(DoublyLinkedList<Data> *dll){
    std::cout << "\nInserting set {0...9} at head" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        dll->addToDLLHead(i);
    }

    std::cout << "Removing and testing elements from head: list contents = ";
    dll->printAll();

    count = 9;
    while (!dll->isEmpty()){
        popped = dll->deleteFromDLLHead().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count--;
    }

    std::cout << "Insert and removed from head test passed" << std::endl;
    return 1;
}

int dllInsertHeadRemoveTail(DoublyLinkedList<Data> *dll){

    std::cout << "\nInserting set {0...9} at head" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        dll->addToDLLHead(i);
    }

    std::cout << "-Removing and testing elements from tail: list contents = ";
    dll->printAll();

    count = 0;
    while (!dll->isEmpty()){
        popped = dll->deleteFromDLLTail().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count++;
    }

    std::cout << "Insert at head and removed from tail test passed" << std::endl;
    return 1;
}

int dllInsertRemoveTail(DoublyLinkedList<Data> *dll){

    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        dll->addToDLLTail(i);
    }

    std::cout << "-Removing and testing elements from tail: list contents = ";
    dll->printAll();

    count = 9;
    while (!dll->isEmpty()){
        popped = dll->deleteFromDLLTail().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count--;
    }

    std::cout << "Insert at tail and removed from tail test passed" << std::endl;
    return 1;
}

int dllInsertTailRemoveHead(DoublyLinkedList<Data> *dll){

    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;
    int count = 0;

    for (int i = 0; i < 10; i++){
        dll->addToDLLTail(i);
    }

    std::cout << "-Removing and testing elements from head: List contents = ";
    dll->printAll();

    count = 0;
    while (!dll->isEmpty()) {
        popped = dll->deleteFromDLLHead().inInt;
        if (popped != count) {
            std::cout << "Expected: " << count << "  got: " << popped << std::endl;
            return 0;
        }
        count++;
    }

    std::cout << "Insert at tail and removed head test passed" << std::endl;
    return 1;
}

int dllInsertTailRemoveEvenOdds(DoublyLinkedList<Data> *dll){
    std::cout << "\nInserting set {0...9} at tail" << std::endl;

    int popped = -1;

    for (int i = 0; i < 10; i++){
        dll->addToDLLTail(i);
    }

    std::cout << "-Removing even numbers from list: List contents = ";
    dll->printAll();

    for (int i = 0; i < 10; i+=2) { dll->deleteNode(i); }
    for (int i = 0; i < 10; i+=2) {
        if (dll->isInList(i)){
            std::cout << "Expected " << i << " to not be in list" << std::endl;
            return 0;
        }
    }

    std::cout << "list contents after removal: ";
    dll->printAll();

    std::cout << "-Removing Odd numbers from list" << std::endl;
    for (int i = 0; i < 10; i+=2) { dll->deleteNode(i + 1); }
    for (int i = 0; i < 10; i+=2) {
        if (dll->isInList(i + 1)){
            std::cout << "Expected " << i + 1 << " to not be in list" << std::endl;
            return 0;
        }
    }

    std::cout << "Insert at tail and removed Even and Odds from head test passed" << std::endl;
    return 1;
}

int dllCharacterTest(DoublyLinkedList<Data> *dll){
    std::cout << "\nCharacter Insert and delete test: Inserting hello, world into list" << std::endl;

    char hello_world[13] = {'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'};

    for (int i = 0; i < 13; i++){
        dll->addToDLLTail(hello_world[i]);
    }

    std::cout << "Double Link list Contents: ";
    dll->printAll();

    for (int i = 0; i < 13; i++){
        char chr = dll->deleteFromDLLHead().inChar;
        if (chr != hello_world[i]){
            std::cout << "Expected character on head remove: " << hello_world[i] << std::endl;
            return 0;
        }
    }

    std::cout << "Insert character string: 'Hello, world' and removed passed" << std::endl;

    return 1;
}

// ==================================================================
// Run all the test     Run all the test
// ==================================================================

int runTest(SingleLinkList<Data> *sll, DoublyLinkedList<Data> *dll){
    // runs a series of test. if any fail return 0 else return 1

    std::cout << "Running Single and Double link list test" << std::endl;

    if (sll == nullptr || dll == nullptr) { return 0; }

    std::cout << " == Testing Single Link List class with Integers == " << std::endl;

    if (!sllInsertRemoveHead(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;
    if (!sllInsertHeadRemoveTail(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;
    if (!sllInsertRemoveTail(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;
    if (!sllInsertTailRemoveHead(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;
    if (!sllInsertTailRemoveEvenOdds(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;

    std::cout << "\n== Testing Single Link List class with Characters == " << std::endl;

    if (!sllCharacterTest(sll)) return 0;
    if (!sllIsEmpty(sll)) return 0;

    std::cout << "\n\n == Testing Double Link List class with Integers == " << std::endl;

    if (!dllInsertRemoveHead(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;
    if (!dllInsertHeadRemoveTail(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;
    if (!dllInsertRemoveTail(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;
    if (!dllInsertTailRemoveHead(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;
    if (!dllInsertTailRemoveEvenOdds(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;

    std::cout << "\n == Testing Double Link List class with Characters == " << std::endl;

    if (!dllCharacterTest(dll)) return 0;
    if (!dllIsEmpty(dll)) return 0;

    std::cout << "\n\nAll test passed\n" << std::endl;

    return 1;
}

// ==================================================================
// entry point
// ==================================================================

int main(int argc, char* argv[]) {

    // single and double link list of class Data to store both either int and char
    SingleLinkList<Data> sll;
    DoublyLinkedList<Data> dll;

    // to run a test. start the program with argument --test
    if ((argc > 1) && (strcmp(argv[1] , "--test") == 0) && !(runTest(&sll, &dll))) {
        std::cout << std::endl << "Test Failed" << std::endl;
        exit(1);
    }

    char inChar;
    int inOp;

    while (true){

        printMenu();

        getOperation(inOp, inChar);

        if (inOp == 12) { break; }

        if (inOp == -1) {
            std::cout << "No operations was selected: please enter number from menu";
            continue;
        }else if (inOp > 12){
            std::cout << "Unknown operation selected: please enter number from menu";
            continue;
        }

        std::cout << std::endl;
        Data *data = nullptr;

        switch(inOp) {
            case 0: // insert at head of single link list
                constructData(data);
                sll.addToHead(*data);
                break;
            case 1: // insert at tail of single link list
                constructData(data);
                sll.addToTail(*data);
                break;
            case 2: // delete head from single link list
                if (sll.isEmpty()) { emptyList(); break; }
                sll.deleteFromHead();
                break;
            case 3: // delete tail from single link list
                if (sll.isEmpty()) { emptyList(); break; }
                sll.deleteFromTail();
                break;
            case 4: // remove node from middle single link list
                constructData(data);
                if (sll.isEmpty()) { emptyList(); break; }
                if (!sll.isInList(*data)) { notFound(); break; }
                sll.deleteNode(*data);
                break;
            case 5: // print all the elements in single link list
                sll.printAll();
                break;
            case 6: // insert at head of double link list
                constructData(data);
                dll.addToDLLHead(*data);
                break;
            case 7: // insert at tail of double link list
                constructData(data);
                dll.addToDLLTail(*data);
                break;
            case 8: // delete head from double link list
                if (dll.isEmpty()) { emptyList(); break; }
                dll.deleteFromDLLHead();
                break;
            case 9: // delete tail of double link list
                if (dll.isEmpty()) { emptyList(); break; }
                dll.deleteFromDLLTail();
                break;
            case 10: // remove node from middle double link list
                constructData(data);
                if (dll.isEmpty()) { emptyList(); break; }
                if (!dll.isInList(*data)) {notFound(); break; }
                dll.deleteNode(*data);
                break;
            case 11: // print all the elements in double link list
                dll.printAll();
                break;
            default: // whoops
                std::cout << "Unknown operation selected: please enter number from menu";
                break;
        }
    }

    sll.clear();
    dll.clear();

    std::cout << "Goodbye" << std::endl;

    return 0;
}
