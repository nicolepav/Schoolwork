#ifndef H_QUEUEFILE
#define H_QUEUEFILE

using namespace std;

template <class Type> class queueADT
{
    public:
        virtual bool isEmptyQueue() const = 0;
            //Function to determine whether the queue is empty. 
            //Postcondition: Returns true if the queue is empty, 
            // otherwise returns false.
        virtual bool isFullQueue() const = 0;
            //Function to determine whether the queue is full. 
            //Postcondition: Returns true if the queue is full, 
            // otherwise returns false.
        virtual void initializeQueue() = 0;
            //Function to initialize the queue to an empty state. 
            //Postcondition: The queue is empty.
        virtual Type front() const = 0;
            //Function to return the first element of the queue. 
            //Precondition: The queue exists and is not empty. 
            //Postcondition: If the queue is empty, the program
            //               terminates; otherwise, the first
            // element of the queue is returned.
        virtual Type back() const = 0;
            //Function to return the last element of the queue. 
            //Precondition: The queue exists and is not empty. 
            //Postcondition: If the queue is empty, the program
            //               terminates; otherwise, the last
            // element of the queue is returned.
        virtual void addQueue(const Type& queueElement) = 0; 
            //Function to add queueElement to the queue. 
            //Precondition: The queue exists and is not full. 
            //Postcondition: The queue is changed and queueElement
            // is added to the queue.
        virtual void deleteQueue() = 0;
            //Function to remove the first element of the queue. 
            //Precondition: The queue exists and is not empty.
            //Postcondition: The queue does no exist
};


template <class Type>
class queueType: public queueADT<Type> {
    public:
        const queueType<Type>& operator=(const queueType<Type>&); //Overload the assignment operator.
        bool isEmptyQueue() const;
            //Function to determine whether the queue is empty. 
            //Postcondition: Returns true if the queue is empty, 
            // otherwise returns false.
        bool isFullQueue() const;
            //Function to determine whether the queue is full. 
            //Postcondition: Returns true if the queue is full, 
            // otherwise returns false.
        void initializeQueue();
            //Function to initialize the queue to an empty state. 
            //Postcondition: The queue is empty.
        Type front() const;
            //Function to return the first element of the queue. 
            //Precondition: The queue exists and is not empty. 
            //Postcondition: If the queue is empty, the program
            //               terminates; otherwise, the first
            //               element of the queue is returned.
        Type back() const;
            //Function to return the last element of the queue. 
            //Precondition: The queue exists and is not empty. 
            //Postcondition: If the queue is empty, the program
            //               terminates; otherwise, the last
            //               element of the queue is returned.
        void addQueue(const Type& queueElement);
            //Function to add queueElement to the queue. 
            //Precondition: The queue exists and is not full. 
            //Postcondition: The queue is changed and queueElement
            // is added to the queue.
        void deleteQueue();
            // function to remove the first element of the queue. 
            //Precondition: The queue exists and is not empty. 
            //Postcondition: The queue is changed and the first 
            //               element is removed from the queue.
        
        queueType(int queueSize = 100); //Constructor
        ~queueType(); //Destructor
    
    private:
        int maxQueueSize; 
        int count;
        int queueFront; 
        int queueRear; 
        Type *list;
};


// FUNCTIONS //


template <class Type>
bool queueType<Type>::isEmptyQueue() const 
{
    return (count == 0); 
} //end isEmptyQueue

template <class Type>
bool queueType<Type>::isFullQueue() const 
{
    return (count == maxQueueSize); 
} //end isFullQueue

template <class Type>
void queueType<Type>::initializeQueue() 
{
    queueFront = 0;
    queueRear = maxQueueSize - 1;
    count = 0;
} //end initializeQueue

template <class Type>
Type queueType<Type>::front() const 
{
    assert(!isEmptyQueue());
    return list[queueFront]; 
} //end front

template <class Type>
Type queueType<Type>::back() const 
{
    assert(!isEmptyQueue());
    return list[queueRear]; 
} //end back

template <class Type>
void queueType<Type>::addQueue(const Type& newElement) 
{
    if (!isFullQueue()) 
    {
        queueRear = (queueRear + 1) % maxQueueSize; //use the 
                            //mod operator to advance queueRear
                            //because the array is circular
        count++;
        list[queueRear] = newElement; 
    }
    else {
        cout << "Cannot add to a full queue." << endl;
    }
} //end addQueue

template <class Type>
void queueType<Type>::deleteQueue() 
{
    if (!isEmptyQueue()) 
    {
        count--;
        queueFront = (queueFront + 1) % maxQueueSize; //use the
                            //mod operator to advance queueFront 
                            //because the array is circular
    }
    else {
        cout << "Cannot remove from an empty queue." << endl;
    }
} //end deleteQueue

template <class Type> 
queueType<Type>::queueType(int queueSize) 
{
    if (queueSize <= 0) 
    {
        cout << "Size of the array to hold the queue must " << "be positive." << endl;
        cout << "Creating an array of size 100." << endl; maxQueueSize = 100;
    }
    else {
        maxQueueSize = queueSize;
    }

    queueFront = 0;
    queueRear = maxQueueSize - 1; 
    count = 0;
    list = new Type[ maxQueueSize] ;
} //end constructor

template <class Type> 
queueType<Type>::~queueType() 
{
    delete [] list; 
}

#endif