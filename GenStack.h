#ifndef GEN_STACK_
#define GEN_STACK_

//stack is template to allow it to be generic
// T to store any data type neded
template<typename T>
class GenStack
{
private:
	T* items;		// Pointer of type T to point to the array
	int top;        // top of the stack
	int stackSize;

public:

    //constructor that takes the desired size of the stack
	GenStack(int size)
	{
        stackSize = size;
        //creating an array of type T with size stackSize
        //the pointer items points to this array
		items = new T[stackSize];

        //top =  -1 to indicate an empty stack
		top = -1;
	}


	bool isEmpty() const
	{
        // if top is -1 then the stack is empty
		return top == -1;
	}

    //push an element to the stack, parameter is const to not change thte data that
    // will be pushed onto the stack and passed by reference to avoid memory and performance overhead
	void push(const T& newEntry)
	{
        // check if the stack is full, it is full when the index of top is the stackSize - 1
		if (top == stackSize - 1)
        {
            //when stack is full allocate a new array with 100 more free spaces
            T* newArray = new T[stackSize + 100];

            //copy data from the old array to the new array
            copyStack(items, newArray);

            //delete the old array to free it's memory
            delete items;

            //make the new array our default array
            items = newArray;

            //update our stack size
            stackSize += 100;
        }

        //increment top by one to point the new free location in the stack
		top++;
        //add the new entry on the top of the stack
		items[top] = newEntry;
	}

    //pop function takes a variable of type T passed by reference
    //and assign the top of the stack to it
	bool pop(T& TopEntry)
	{
        //check if the stack is empty
		if (isEmpty()) return false;

        //assiging top of the stack to the variable passed by reference
		TopEntry = items[top];

        //decrement the top by one to discard the last element
		top--;

		return true;
	}

    //removes the top of the stack
    bool pop()
	{
        //check if the stack is empty
		if (isEmpty()) return false;
        //decrement the rop by one to discard the last element
		top--;
		return true;
	}

    // get the top element
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}

private:
    //function that copies the data of stack from the old array to the new array when the old is full
    void copyStack(T* oldArray, T* newArray)
    {
        //looping on all the elements of the old array and copy them to the new array
        for (int i = 0; i < stackSize; i++)
        {
            newArray[i] = oldArray[i];
        }
    }
}; 

#endif
