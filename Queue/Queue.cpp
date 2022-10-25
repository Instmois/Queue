
#include <iostream>
#include <cstdlib>
using namespace std;

class Queue {

    int start = -1;
    int end = -1;
    int size = 5;
    int* buffer = new int[size];

    bool IsFull() const {
        return ((end + 1) % size == start);
    }

public:
    // Конструктор копирования.
    // Оператор копирующего присваивания.
    Queue() = default;
    ~Queue() {
        delete[] buffer;
    }
    Queue(const Queue& Que) {
            start = Que.start;
            end = Que.end;
            for (int i = Que.start; i <= Que.end; i = (i + 1) % size) {
                buffer[i] = Que.buffer[i];
                buffer[end] = Que.buffer[end];
            }
            
    }
    bool IsEmpty() const {
        return (start == end && end == -1);
    }

    int counter() const {
        if (IsEmpty()) return 0;
        return (end >= start) ? (end - start + 1) : (size - (start - end - 1));
    }
    int front() const {
        if (IsEmpty()) exit(1);
        return buffer[start];
    }
    int back() const {
        if (IsEmpty()) exit(1);
        return buffer[end];
    }
    void reset() {
        start = end = -1;
    }
    bool pop() {
        if (IsEmpty()) return false;
        if (start == end) start = end = -1;
        else start = (start + 1) % size;
        return true;
    }
    bool push(int element) {
        if (IsEmpty()) start = end = 0;
        else {
            if (IsFull()) {
                int* new_buffer = new int[size * 2];
                int i = start, j = 0;
                while (i != end) {
                    new_buffer[j] = buffer[i];
                    i = (i + 1) % size;
                    j++;
                }
                new_buffer[j] = buffer[i];
                start = 0;
                end = j;
                size *= 2;
                delete[] buffer;
                buffer = new_buffer;
            }
            end = (end + 1) % size;
        }
        buffer[end] = element;
        return true;
    }

    void print() const {
        if (IsEmpty()) cout << "The qeueu is empty \n";
        else if (end == start) cout << buffer[start] << endl;
        else {
            cout << "start = ";
            int i = start;
            while (i != end) {
                cout << buffer[i] << " -> ";
                i = (i + 1) % size;
            }
            cout << buffer[i] << endl;
        }
    }
    Queue& operator=(const Queue& Que) {
        int* new_buffer = new int[Que.size];
        start = Que.start;
        end = Que.end;
        size = Que.size;
        for (int i = start;  i != end; i = (i + 1) % size) {
            new_buffer[i] = Que.buffer[i];
        }
        new_buffer[end] = Que.buffer[end];
        delete[] buffer;
        buffer = new_buffer;
        return *this;
    }
};

int main()
{
    Queue q1;
    Queue q2;
    q2.push(1);
    q2.push(2);
    q2.push(3);
    q2.push(4);
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);
    q1.pop();
    q1.push(6);
    q1.push(7);
    q1.print();
    q2.print();
    Queue q3(q2);
    q3.print();
    q2 = q1;
    q2.print();
    return 0;
}