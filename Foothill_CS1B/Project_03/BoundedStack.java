public class BoundedStack<E> {

    public class Node<E> {

        protected Node<E> next;
        private E data;

        public Node() {
            next = null;
        }
        public Node(E data) {
            setData(data);
        }

        public boolean setData(E data) {
            if (data == null)
                return false;
            this.data = data;
            return true;
        }

        public E getData() {
            return data;
        }

        // console display
        public String toString() {
            return data.toString();
        }
    }


    private Node<E> top;
    private static int stacksize;

    private void overflow() {
        Node<E> p = top;
        Node<E> q = null;
        while(p.next != null) {
            q = p;
            p = p.next;
        }
        q.next = null;
        stacksize--;
    }

    public BoundedStack() { top = null; }

    public boolean isEmpty() { return top == null; }

    public void push(E data)
    {
        if (data == null) { return; };
        if (stacksize == 50) { this.overflow(); };

        Node<E> newNode = new Node<E>(data);
        newNode.next = top;
        top = newNode;
        stacksize++;
    }

    public E pop()
    {
        if (isEmpty()) { return null; };

        Node<E> temp;
        temp = top;
        top = top.next;

        stacksize--;
        return temp.getData();
    }

    public String toString()
    {
        Node p;
        String showAll = "";
        for( p = top; p != null; p = p.next ) {
            showAll += p.toString() + "\n";
        }
        return showAll;
    }

}
