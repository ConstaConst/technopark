#include <iostream>
#include <cassert>

#define  assert( false )

//Очередь на односвязном списке.
//Из head pop в tail(-> nullptr) push
class CQueue {
public:
    ~CQueue();

    //Добавление элемента в конец очереди
    void Push( int data );
    //Извлечение элемента. Если очередь пуста, то assert.
    int Pop();
    //Пуста ли очередь
    bool IsEmpty() const { return head == tail; }

private:
    //Узел односвязного списка.
    struct CQueueNode {
        int Data;
        CQueueNode* Next;
        explicit CQueueNode( int data ) : Data( data ), Next( nullptr ) {}//explicit для конструкторов с одной переменной!
    };
    CQueueNode* head = nullptr;
    CQueueNode* tail = nullptr;
};

CQueue::~CQueue()
{
    while( !IsEmpty() ) {
        CQueueNode* toDelete = head;
        head = head->Next;
        delete toDelete;
    }
}

void CQueue::Push( int data )
{
    CQueueNode* newNode = new CQueueNode( data );
    if( head == nullptr ) {
        assert( tail == nullptr );
        head = tail = newNode;
    } else {
        assert( tail != nullptr );//Всегда проверять указатель перед разыменованием!!!
        tail->Next = newNode;
        tail = newNode;
    }
}

int CQueue::Pop()
{
    assert( head != nullptr )
    assert( tail != nullptr )

    //Запоминаем данные, которые надо вернуть.
    const int data = head->Data;
    //Узел, который хотим удалить.
    CQueueNode* toDelete = head;
    //Сдвигаем head.
    head = head->Next;
    //Если в очереди был ровно один элемент, то head == 0, обнулим tail.

    delete toDelete;

    return data;
}

int main() {

    int commandsCount = 0;

    std::cin >> commandsCount;
    assert( commandsCount >= 0);

    CQueue queue;
    for( int i = 0; i < commandsCount; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch ( command ) {
            case 3:
                queue.Push( value );
                break;
            case 2:
                if ( queue.IsEmpty() && value != -1 || !queue.IsEmpty() && queue.Pop() != value) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            default:
                assert( false );
        }
    }

    std::cout << "YES";
    return 0;
}