#ifndef HEADER_H
#define HEADER_H

class Exception{
    public:
        virtual const char* er() const{
            return "Error";
        }
};

class Out_of_range: public Exception{
    public:
        virtual const char* er() const{
            return "index out of range";
        }
};

class Stack_is_empty: public Exception{
    public:
        virtual const char* er() const{
            return "stack is empty";
        }
};

class Vector_is_empty: public Exception{
    public:
        virtual const char* er() const{
            return "vector is empty";
        }
};

class Negative_element: public Exception{
    public:
        virtual const char* er() const{
            return "the number of elements can't be negative";
        }
};

class Eror_in_reading_element: public Exception{
    public:
        virtual const char* er() const{
            return "error in reading elements";
        }
};

class Eror_in_resize: public Exception{
    public:
        virtual const char* er() const{
            return "resize error";
        }
};
#endif