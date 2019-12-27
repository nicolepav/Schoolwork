//Class Stack ---------------------------------------
class Stack<E>
{
    // pointer to first node in stack
    private Node<E> top;

    // constructor
    public Stack()
    {
        top = null;
    }

    public boolean isEmpty()
    {
        return top == null;
    }

    public void push(E data)
    {
        if (data == null)
            return;
        // build a node and place it on the stack
        Node<E> newNode = new Node<E>(data);
        newNode.next = top;
        top = newNode;
    }

    public E pop()
    {
        Node<E> temp;

        temp = top;
        if (isEmpty())
            return null;

        top = top.next;
        return temp.getData();
    }

    // console display
    public String toString()
    {
        Node p;

        String showAll = "";
        // Display all the nodes in the stack
        for( p = top; p != null; p = p.next )
            showAll += p.toString() + "\n";
        return showAll;
    }
}