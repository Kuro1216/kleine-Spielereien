template <typename T>
class Liste{
private:
    T *_values;
    int _last, _size;

    int isFull(void);
    int find(T value);
    void increase(void);
    void decrease(void);
public:
    Liste(int size = 8);
    Liste(const Liste& l);
    ~Liste();
    void append(T value);
    void remove(T value);
    void remove(int value);
    T getValueAt(int pos);
    int size();

    T operator[](int pos);
    Liste operator=(const Liste& l);
};


template <typename T>
Liste<T>::Liste(int size) {
    _size = size;
    _last = 0;
    _values = new T[size];
}


template <typename T>
Liste<T>::Liste(const Liste& l) {
    _size = l._size;
    _last = l._last;
    _values = new T[_size];

    for (int i = 0; i < _last; i++)
        _values[i] = l._values[i];
}


template <typename T>
Liste<T>::~Liste() {
    delete[] _values;
}


template <typename T>
void Liste<T>::increase() {
    T *tmp = new T[_size * 2];

    for (int i = 0; i < _size; i++)
        tmp[i] = _values[i];

    delete[] _values;
    _values = tmp;
    _size *= 2;
}


template <typename T>
void Liste<T>::decrease() {
    _size /= 2;
    T *tmp = new T[_size];

    for (int i = 0; i < _size; i++)
        tmp[i] = _values[i];

    delete[] _values;
    _values = tmp;
}


template <typename T>
int Liste<T>::isFull() {
    return _last == _size;
}


template <typename T>
int Liste<T>::find(T val) {
    int pos;

    for (pos = 0; pos < _last; pos++)
        if (_values[pos] == val)
            return pos;
    return -1;
}


template <typename T>
T Liste<T>::getValueAt(int pos) {
    if (pos < 0 || pos >= _last)
        throw "OutOfBoundsException";

    return _values[pos];
}


template <typename T>
void Liste<T>::append(T val) {
    if (isFull())
        increase();

    _values[_last] = val;
    _last += 1;
}


template <typename T>
void Liste<T>::remove(T value) {
    int pos = find(value);

    if (pos == -1)
        throw "ValueNotFoundException";

    for (; pos < _last -1; pos++)
        _values[pos] = _values[pos + 1];
    _last -= 1;

    if (_last < _size / 4)
        decrease();
}

template <typename T>
void Liste<T>::remove(int value){
    for (int pos = value; pos < _last -1; pos++)
        _values[pos] = _values[pos + 1];
    _last -= 1;

    if (_last < _size / 4)
        decrease();
}

template <typename T>
int Liste<T>::size() {
    return _last;
}


template <typename T>
T Liste<T>::operator[](int pos) {
    return getValueAt(pos);
}


template <typename T>
Liste<T> Liste<T>::operator=(const Liste& l) {
    if (this != &l) {
        delete[] _values;

        _size = l._size;
        _last = l._last;
        _values = new T[_size];

        for (int i = 0; i < _last; i++)
            _values[i] = l._values[i];
    }
    return *this;
}
