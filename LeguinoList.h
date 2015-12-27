#ifndef __LEGUINO_LIST_H
#define __LEGUINO_LIST_H


#include "LeguinoPanic.h"


template <class ELEMENTTYPE> class ValueList
{
	public:

		ValueList();
		virtual ~ValueList();
		void append(ELEMENTTYPE element);
		ELEMENTTYPE get(int no) const;
		inline int getCount() const;
		ELEMENTTYPE getFirst() const;
		ELEMENTTYPE getLast() const;
		void insert(int no, ELEMENTTYPE element);
		inline bool isEmpty() const;
		inline void prepend(ELEMENTTYPE element);
		ELEMENTTYPE set(int no, ELEMENTTYPE newElement);
		void unlinkAll();
		ELEMENTTYPE unlinkAt(int no);
		ELEMENTTYPE unlinkElement(ELEMENTTYPE element);
		bool unlinkRange(int from, int count);
		inline ELEMENTTYPE unlinkFirst();
		ELEMENTTYPE unlinkLast();

	protected:

		int count;
		ELEMENTTYPE * elements;
		int size;

		void checkSize(int newSize);
};

template <class ELEMENTTYPE> class ObjectList : public ValueList<ELEMENTTYPE>
{
	public:

		virtual ~ObjectList();
		void deleteAll();
		bool deleteAt(int no);
		bool deleteElement(ELEMENTTYPE element);
		inline bool deleteFirst();
		bool deleteLast();
		bool deleteRange(int from, int count);
};


template <class ELEMENTTYPE> ValueList<ELEMENTTYPE>::ValueList()
{
	count = 0;
	elements = NULL;
	size = 0;

	checkSize(1);
}

template <class ELEMENTTYPE> ValueList<ELEMENTTYPE>::~ValueList()
{
	unlinkAll();
	if (elements) {delete elements; elements = NULL;}
}

template <class ELEMENTTYPE> void ValueList<ELEMENTTYPE>::append(ELEMENTTYPE element)
{
	checkSize(count + 1);
	elements[count++] = element;
}

template <class ELEMENTTYPE> void ValueList<ELEMENTTYPE>::checkSize(int newSize)
{
	if (newSize <= size)
		return;

	size = newSize + 3;

	ELEMENTTYPE * newElements;
	if ((newElements = new ELEMENTTYPE[size]) == NULL)
		panic();
	memset(newElements, 0, sizeof(ELEMENTTYPE) * size);

	if (elements)
	{
		memmove(newElements, elements, sizeof(ELEMENTTYPE) * count);
		delete elements;
	}

	elements = newElements;
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::get(int no) const
{
	if (no < 0 || no >= count)
		return NULL;

	return elements[no];
}

template <class ELEMENTTYPE> inline int ValueList<ELEMENTTYPE>::getCount() const
{
	return count;
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::getFirst() const
{
	if (count <= 0)
		return NULL;

	return elements[0];
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::getLast() const
{
	if (count <= 0)
		return NULL;

	return elements[count-1];
}

template <class ELEMENTTYPE> void ValueList<ELEMENTTYPE>::insert(int no, ELEMENTTYPE element)
{
	if (no < 0 || no > count)
		return;

	checkSize(count + 1);

	memmove(&elements[no+1], &elements[no], sizeof(ELEMENTTYPE) * (count - no));
	count++;
	elements[no] = element;
}

template <class ELEMENTTYPE> inline bool ValueList<ELEMENTTYPE>::isEmpty() const
{
	return count <= 0;
}

template <class ELEMENTTYPE> inline void ValueList<ELEMENTTYPE>::prepend(ELEMENTTYPE element)
{
	insert(element, 0);
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::set(int no, ELEMENTTYPE newElement)
{
	if (no < 0)
		return NULL;

	checkSize(no + 1);

	ELEMENTTYPE oldElement = elements[no];
	elements[no] = newElement;
	return oldElement;
}

template <class ELEMENTTYPE> void ValueList<ELEMENTTYPE>::unlinkAll()
{
	checkSize(0);
	count = 0;
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::unlinkAt(int no)
{
	if (no < 0 || no >= count)
		return NULL;

	ELEMENTTYPE oldElement = elements[no];
	memmove(&elements[no], &elements[no+1], sizeof(ELEMENTTYPE) * (count - no - 1));

	checkSize(count - 1);
	count--;

	return oldElement;
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::unlinkElement(ELEMENTTYPE element)
{
	for (int i=0; i<count; i++)
		if (elements[i] == element)
			return unlinkAt(i);

	return NULL;
}

template <class ELEMENTTYPE> bool ValueList<ELEMENTTYPE>::unlinkRange(int from, int count)
{
	if (from < 0 || count < 0 || from + count > this->count)
		return false;

	memmove(&elements[from], &elements[from + count], sizeof(ELEMENTTYPE) * (this->count - from - count));

	checkSize(this->count - count);
	this->count -= count;

	return true;
}

template <class ELEMENTTYPE> inline ELEMENTTYPE ValueList<ELEMENTTYPE>::unlinkFirst()
{
	return unlinkAt(0);
}

template <class ELEMENTTYPE> ELEMENTTYPE ValueList<ELEMENTTYPE>::unlinkLast()
{
	if (count <= 0)
		return NULL;

	ELEMENTTYPE oldElement = elements[count - 1];

	checkSize(count - 1);
	count--;

	return oldElement;
}


template <class ELEMENTTYPE> ObjectList<ELEMENTTYPE>::~ObjectList()
{
	deleteAll();
}

template <class ELEMENTTYPE> void ObjectList<ELEMENTTYPE>::deleteAll()
{
	for (int i=0; i<this->count; i++)
		delete this->elements[i];

	this->checkSize(0);
	this->count = 0;
}

template <class ELEMENTTYPE> bool ObjectList<ELEMENTTYPE>::deleteAt(int no)
{
	ELEMENTTYPE deleteElement;
	if ((deleteElement = ValueList<ELEMENTTYPE>::unlinkAt(no)) != NULL)
	{
		delete (ELEMENTTYPE) deleteElement;
		return true;
	}
	else
		return false;
}

template <class ELEMENTTYPE> bool ObjectList<ELEMENTTYPE>::deleteElement(ELEMENTTYPE element)
{
	ELEMENTTYPE deleteElement;
	if ((deleteElement = ValueList<ELEMENTTYPE>::unlinkElement(element)) != NULL)
	{
		delete (ELEMENTTYPE) deleteElement;
		return true;
	}
	else
		return false;
}

template <class ELEMENTTYPE> inline bool ObjectList<ELEMENTTYPE>::deleteFirst()
{
	return deleteAt(0);
}

template <class ELEMENTTYPE> bool ObjectList<ELEMENTTYPE>::deleteLast()
{
	ELEMENTTYPE deleteElement;

	if ((deleteElement = this->unlinkLast()) != NULL)
	{
		delete (ELEMENTTYPE) deleteElement;
		return true;
	}
	else
		return false;
}

template <class ELEMENTTYPE> bool ObjectList<ELEMENTTYPE>::deleteRange(int from, int count)
{
	if (from < 0 || count < 0 || from + count > this->count)
		return false;

	for (int i=from; i<from + count; i++)
		delete this->elements[i];

	memmove(&this->elements[from], &this->elements[from + count],
		sizeof(ELEMENTTYPE) * (this->count - from - count));
	this->checkSize(this->count - count);

	this->count -= count;

	return true;
}


#endif
