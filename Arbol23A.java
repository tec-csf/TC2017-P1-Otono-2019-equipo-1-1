
import java.util.Scanner;

class Tree23<T extends Comparable<T>> {



    private static final int ROOT_IS_BIGGER = 1;

    private static final int ROOT_IS_SMALLER = -1;



    private Node root;

    private int size;

    private boolean addition;



    Tree23() {

        this.root = new Node();

        this.size = 0;

    }



    public boolean isEmpty() {

        if (root == null) return true;

        return root.getLeftElement() == null;

    }





    public boolean contains(T element) {

        return search(element);

    }



    public int size() {

        return size;

    }



    public void add(T element) {



        size++;

        addition = false;



        if (root == null || root.getLeftElement() == null) { // ?????? ??????

            if (root == null) {

                root = new Node();

            }

            root.setLeftElement(element);

            addition = true;



        } else {

            Node newRoot = add(root, element);

            if (newRoot != null) {

                root = newRoot;

            }

        }



        if (!addition) size--;

    }



    private Node add(Node current, T element) {



        Node newParent = null;

        if (!current.isLeaf()) {



            Node newNode;


            if (current.leftElement.compareTo(element) == 0 || (current.is3Node() && current.rightElement.compareTo(element) == 0)) {

            }



            else if (current.leftElement.compareTo(element) == ROOT_IS_BIGGER) {

                newNode = add(current.left, element);




                if (newNode != null) {




                    if (current.is2Node()) {

                        current.rightElement = current.leftElement;

                        current.leftElement = newNode.leftElement;

                        current.right = current.mid;

                        current.mid = newNode.mid;

                        current.left = newNode.left;

                    }





                    else {



                        Node rightCopy = new Node(current.rightElement, null, current.mid, current.right);




                        newParent = new Node(current.leftElement, null, newNode, rightCopy);

                    }

                }

            }



            else if (current.is2Node() || (current.is3Node() && current.rightElement.compareTo(element) == ROOT_IS_BIGGER)) {



                newNode = add(current.mid, element);



                if (newNode != null) {



                    if (current.is2Node()) {

                        current.rightElement = newNode.leftElement;

                        current.right = newNode.mid;

                        current.mid = newNode.left;

                    }




                    else {

                        Node left = new Node(current.leftElement, null, current.left, newNode.left);

                        Node mid = new Node(current.rightElement, null, newNode.mid, current.right);

                        newParent = new Node(newNode.leftElement, null, left, mid);

                    }

                }

            }




            else if (current.is3Node() && current.rightElement.compareTo(element) == ROOT_IS_SMALLER) {



                newNode = add(current.right, element);




                if (newNode != null) {

                    Node leftCopy = new Node(current.leftElement, null, current.left, current.mid);

                    newParent = new Node(current.rightElement, null, leftCopy, newNode);

                }

            }

        }



        else {



            addition = true;




            if (current.leftElement.compareTo(element) == 0 || (current.is3Node() && current.rightElement.compareTo(element) == 0)) {

                addition = false;

            }



            else if (current.is2Node()) {



                if (current.leftElement.compareTo(element) == ROOT_IS_BIGGER) {

                    current.rightElement = current.leftElement;

                    current.leftElement = element;

                }




                else if (current.leftElement.compareTo(element) == ROOT_IS_SMALLER) current.rightElement = element;

            }





            else newParent = split(current, element);

        }



        return newParent;

    }




    private Node split(Node current, T element) {



        Node newParent = null;




        if (current.leftElement.compareTo(element) == ROOT_IS_BIGGER) {

            Node<T> left = new Node<>(element, null);

            Node right = new Node(current.rightElement, null);

            newParent = new Node(current.leftElement, null, left, right);



        } else if (current.leftElement.compareTo(element) == ROOT_IS_SMALLER) {




            if (current.rightElement.compareTo(element) == ROOT_IS_BIGGER) {



                Node left = new Node(current.leftElement, null);

                Node right = new Node(current.rightElement, null);

                newParent = new Node(element, null, left, right);



            }



            else {



                Node left = new Node(current.leftElement, null);

                Node<T> right = new Node<>(element, null);

                newParent = new Node(current.rightElement, null, left, right);

            }

        }



        return newParent;

    }




    public boolean remove(T element) {

        boolean ifRemoved;



        this.size--;



        ifRemoved = remove(root, element);



        root.reBalance();



        if (root.getLeftElement() == null) root = null;



        if (!ifRemoved) this.size++;



        return ifRemoved;

    }




    private boolean remove(Node current, T element) {

        boolean ifRemoved = true;



        if (current == null) {

            ifRemoved = false;

            return false;

        }



        else {



            if (!current.getLeftElement().equals(element)) {



                if (current.getRightElement() == null || current.getRightElement().compareTo(element) == ROOT_IS_BIGGER) {



                    if (current.getLeftElement().compareTo(element) == ROOT_IS_BIGGER) {

                        ifRemoved = remove(current.left, element);

                    }



                    else {

                        ifRemoved = remove(current.mid, element);

                    }



                } else {



                    if (!current.getRightElement().equals(element)) {

                        ifRemoved = remove(current.right, element);

                    }



                    else {


                        if (current.isLeaf()) {

                            current.setRightElement(null);

                        }


                        else {




                            T replacement = (T) current.getRightNode().replaceMin();



                            current.setRightElement(replacement);

                        }

                    }

                }

            }



            else {



                if (current.isLeaf()) {



                    if (current.getRightElement() != null) {

                        current.setLeftElement(current.getRightElement());

                        current.setRightElement(null);



                    }



                    else {

                        current.setLeftElement(null);

                        return true;

                    }

                }




                else {





                    T replacement = (T) current.getLeftNode().replaceMax();

                    current.setLeftElement(replacement);

                }

            }

        }




        if (current != null && !current.isBalanced()) {

            current.reBalance();

        } else if (current != null && !current.isLeaf()) {



            boolean isBalanced = false;



            while (!isBalanced) {



                if (current.getRightNode() == null) {




                    if (current.getLeftNode().isLeaf() && !current.getMidNode().isLeaf()) {

                        T replacement = (T) current.getMidNode().replaceMin();

                        T tempLeft = (T) current.getLeftElement();

                        current.setLeftElement(replacement);



                        add(tempLeft);

                    }


                    else if (!current.getLeftNode().isLeaf() && current.getMidNode().isLeaf()) {



                        if (current.getRightElement() == null) {

                            T replacement = (T) current.getLeftNode().replaceMax();

                            T tempLeft = (T) current.getLeftElement();

                            current.setLeftElement(replacement);



                            add(tempLeft);

                        }

                    }

                }



                if (current.getRightNode() != null) {



                    if (current.getMidNode().isLeaf() && !current.getRightNode().isLeaf()) {

                        current.getRightNode().reBalance();

                    }



                    if (current.getMidNode().isLeaf() && !current.getRightNode().isLeaf()) {

                        T replacement = (T) current.getRightNode().replaceMin();

                        T tempRight = (T) current.getRightElement();

                        current.setRightElement(replacement);



                        add(tempRight);

                    } else {

                        isBalanced = true;

                    }

                }



                if (current.isBalanced()) isBalanced = true;

            }

        }



        return ifRemoved;

    }



    public void clear() {

        this.size = 0;

        this.root = null;

    }




    public boolean search(T element) {

        if (root == null) return false;

        return search(root, element);

    }



    private boolean search(Node current, T element) {

        boolean ifFound = false;



        if (current != null) {




            if (current.leftElement != null && current.leftElement.equals(element)) {

                ifFound = true;

            }




            else {




                if (current.rightElement != null && current.rightElement.equals(element)) {

                    ifFound = true;

                }


                else {

                    if (current.leftElement.compareTo(element) == ROOT_IS_BIGGER) {

                        ifFound = search(current.left, element);



                    } else if (current.right == null || current.rightElement.compareTo(element) == ROOT_IS_BIGGER) {

                        ifFound = search(current.mid, element);



                    } else if (current.rightElement.compareTo(element) == ROOT_IS_SMALLER) {

                        ifFound = search(current.right, element);



                    } else return false;

                }

            }

        }



        return ifFound;

    }



    public T findMin() {

        if (isEmpty()) return null;

        return findMin(root);

    }



    private T findMin(Node current) {




        if (current.getLeftNode() == null) {

            return (T) current.leftElement;

        }




        else {

            return findMin(current.getLeftNode());

        }

    }




    public T findMax() {

        if (isEmpty()) return null;

        return findMax(root);

    }



    private T findMax(Node current) {




        if (current.rightElement != null && current.getRightNode() != null) {

            return findMax(current.getRightNode());

        } else if (current.getMidNode() != null) {

            return findMax(current.getMidNode());

        }




        if (current.rightElement != null) return (T) current.rightElement;

        else return (T) current.leftElement;

    }




    public void inOrder() {



        if (!isEmpty()) inOrder(root);

        else System.out.print("The tree is empty...");

    }



    private void inOrder(Node current) {



        if (current != null) {



            if (current.isLeaf()) {



                System.out.print(current.getLeftElement().toString() + " ");

                if (current.getRightElement() != null) {

                    System.out.print(current.getRightElement().toString() + " ");

                }

            } else {



                inOrder(current.getLeftNode());

                System.out.print(current.getLeftElement().toString() + " ");

                inOrder(current.getMidNode());



                if (current.getRightElement() != null) {



                    if (!current.isLeaf()) {

                        System.out.print(current.getRightElement().toString() + " ");

                    }



                    inOrder(current.getRightNode());

                }

            }

        }

    }



    public void preOrder() {



        if (!isEmpty()) {



            preOrder(root);

        } else System.out.print("The tree is empty...");

    }



    private void preOrder(Node current) {



        if (current != null) {



            System.out.print(current.leftElement.toString() + " ");

            preOrder(current.left);

            preOrder(current.mid);



            if (current.rightElement != null) {



                System.out.print(current.rightElement.toString() + " ");

                preOrder(current.right);

            }

        }

    }




    public void postOrder() {



        if (!isEmpty()) {



            postOrder(root);

        } else System.out.print("The tree is empty...");

    }



    private void postOrder(Node current) {



        if (current != null) {



            postOrder(current.left);

            postOrder(current.mid);

            System.out.print(current.leftElement.toString() + " ");



            if (current.rightElement != null) {



                System.out.print(current.rightElement.toString() + " ");

                postOrder(current.right);

            }

        }

    }



}

class Node<T extends Comparable<T>> {



    Node left;

    Node mid;

    Node right;

    T leftElement;

    T rightElement;



    public Node() {

        this.left = null;

        this.mid = null;

        this.right = null;

        this.leftElement = null;

        this.rightElement = null;

    }





    public Node(T leftElement, T rightElement) {

        this.leftElement = leftElement;

        this.rightElement = rightElement;

        left = null;

        mid = null;

        right = null;

    }




    public Node(T leftElement, T rightElement, Node left, Node mid) {

        this.leftElement = leftElement;

        this.rightElement = rightElement;

        this.left = left;

        this.mid = mid;

    }



    public T getLeftElement() {

        return leftElement;

    }



    public void setLeftElement(T element) {

        this.leftElement = element;

    }



    public T getRightElement() {

        return rightElement;

    }



    public void setRightElement(T element) {

        this.rightElement = element;

    }



    private void setLeftNode(Node left) {

        this.left = left;

    }



    public Node getLeftNode() {

        return left;

    }



    private void setMidNode(Node mid) {

        this.mid = mid;

    }



    public Node getMidNode() {

        return mid;

    }



    private void setRightNode(Node right) {

        this.right = right;

    }



    public Node getRightNode() {

        return right;

    }





    public boolean isLeaf() {

        return left == null && mid == null && right == null;

    }




    public boolean is2Node() {

        return rightElement == null;

    }




    public boolean is3Node() {

        return rightElement != null;

    }




    boolean isBalanced() {



        boolean balanced = false;



        if (isLeaf()) {

            balanced = true;



        } else if (left.getLeftElement() != null && mid.getLeftElement() != null) {


            if (rightElement != null) {

                if (right.getLeftElement() != null) {

                    balanced = true;

                }

            } else {

                balanced = true;

            }

        }



        return balanced;

    }



    public T replaceMax() {



        T max;



        if (isLeaf()) {



            if (getRightElement() != null) {

                max = getRightElement();

                setRightElement(null);


            } else {

                max = getLeftElement();

                setLeftElement(null);


            }

        }




        else {



            if (getRightElement() != null) {

                max = (T) right.replaceMax();

            }



            else {

                max = (T) mid.replaceMax();

            }

        }



        if (!isBalanced()) {

            reBalance();

        }



        return max;

    }




    T replaceMin() {



        T min;



        if (isLeaf()) {



            min = leftElement;

            leftElement = null;




            if (rightElement != null) {

                leftElement = rightElement;

                rightElement = null;

            }

        }




        else {

            min = (T) left.replaceMin();

        }




        if (!isBalanced()) {

            reBalance();

        }



        return min;

    }





    void reBalance() {



        while (!isBalanced()) {




            if (getLeftNode().getLeftElement() == null) {




                getLeftNode().setLeftElement(getLeftElement());




                setLeftElement((T) getMidNode().getLeftElement());




                if (getMidNode().getRightElement() != null) {

                    getMidNode().setLeftElement(getMidNode().getRightElement());

                    getMidNode().setRightElement(null);

                }




                else {

                    getMidNode().setLeftElement(null);

                }



            }



            else if (getMidNode().getLeftElement() == null) {




                if (getRightElement() == null) {



                    if (getLeftNode().getLeftElement() != null && getLeftNode().getRightElement() == null && getMidNode().getLeftElement() == null) {

                        setRightElement(getLeftElement());

                        setLeftElement((T) getLeftNode().getLeftElement());




                        setLeftNode(null);

                        setMidNode(null);

                        setRightNode(null);



                    } else {

                        getMidNode().setLeftElement(getLeftElement());

                        if (getLeftNode().getRightElement() == null) {

                            setLeftElement((T) getLeftNode().getLeftElement());

                            getLeftNode().setLeftElement(null);



                        } else {

                            setLeftElement((T) getLeftNode().getRightElement());

                            getLeftNode().setRightElement(null);

                        }



                        if (getLeftNode().getLeftElement() == null && getMidNode().getLeftElement() == null) {

                            setLeftNode(null);

                            setMidNode(null);

                            setRightNode(null);

                        }

                    }



                } else {




                    getMidNode().setLeftElement(getRightElement());



                    setRightElement((T) getRightNode().getLeftElement());



                    if (getRightNode().getRightElement() != null) {

                        getRightNode().setLeftElement(getRightNode().getRightElement());

                        getRightNode().setRightElement(null);



                    }




                    else {

                        getRightNode().setLeftElement(null);

                    }

                }

            }




            else if (getRightElement() != null && getRightNode().getLeftElement() == null) {




                if (getMidNode().getRightElement() != null) {

                    getRightNode().setLeftElement(getRightElement());

                    setRightElement((T) getMidNode().getRightElement());

                    getMidNode().setRightElement(null);



                }




                else {

                    getMidNode().setRightElement(getRightElement());

                    setRightElement(null);

                }

            }

        }

    }

}


//El código fue obtenido de la siguiente liga https://github.com/SValentyn/2-3-tree/tree/master/src
