#ifndef POLYGON_BASE_REGULAR_POLYGON_HPP
#define POLYGON_BASE_REGULAR_POLYGON_HPP

namespace polygon_base
{
    class RegularPolygon
    {
        public:
            virtual void initialize(double side_length) = 0;
            virtual double area() = 0;
            virtual ~RegularPolygon() {} //destructor clean up after using the class
            
        protected:
            RegularPolygon() {}
    };
}

#endif // POLYGON_BASE_REGULAR_POLYGON_HPP