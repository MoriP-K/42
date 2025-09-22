template <typename T>
Array<T>::Array(): _arr(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n): _arr(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(Array const &copy): _arr(new T[copy._size]), _size(copy._size)
{
	for (unsigned int i = 0; i < _size; i++)
	{
		_arr[i] = copy._arr[i];
	}
	
}

template <typename T>
Array<T>::~Array()
{
	delete [] _arr;
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &copy)
{
	if (this != &copy)
	{
		delete [] this->_arr;
		this->_size = copy._size;
		this->_arr = new T[_size];
		for (unsigned int i = 0; i < this->_size; i++)
			this->_arr[i] = copy._arr[i];
	}
	return (*this);
}

template <typename T>
T &Array<T>::operator[](unsigned int i)
{
	if (i >= this->_size)
		throw OutOfBoundsException();
	return (this->_arr[i]);
}

template <typename T>
T const &Array<T>::operator[](unsigned int i) const
{
	if (i >= this->_size)
		throw OutOfBoundsException();
	return (this->_arr[i]);
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (this->_size);
}

template <typename T>
const char *Array<T>::OutOfBoundsException::what() const throw()
{
	return ("Out of bounds for index.");
}
