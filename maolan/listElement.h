template <class T>
class listElement
{
  public:
    listElement(const T &element, const bool &front = true)
    {
      T *begin = nullptr;
      T *last = nullptr;
      _element = element;
    if (front)
    {
      this->_next = begin;
      if (begin != nullptr)
      {
        begin->_previous = this;
      }
      begin = this;
      if (last == nullptr)
      {
        last = this;
      }
    }
    else
    {
      this->_previous = last;
      last = this;
      if (begin == nullptr)
      {
        begin = this;
      }
    }
    }

    T element() { return _element; }

    listElement<T> * next() { return _next; }
    void next(listElement <T> *n) { _next = n; }

    listElement<T> * previous() { return _previous; }
    void previous(listElement <T> *p) { _previous = p; }

  protected:
    T _element;
    listElement<T> *_next;
    listElement<T> *_previous;

};
