#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////														DYNAMIC ARRAY																////////	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INFO: elementy template mog¹ wspó³istnieæ ze sob¹ jedynie w pliku nag³ówkowym .h
#define DEBUG
//#define WORK

template<class type>
class tab
{
protected:

	//  VARIABLES
	//---------------------------			
	type* array;
	//type* temp_array;
	type* value;
	unsigned int* size_array;
	unsigned int* old_size_array;

	//  FUNCTIONS
	//---------------------------	
	void copy_array(type* wsk);

public:

	//  CONSTRUCTORS
	//---------------------------	
	//default with no params
	tab() : size_array(new unsigned int), old_size_array(new unsigned int), array(new type), value(new type)
	{
		*size_array = 0;
		*old_size_array = 0;
		array = nullptr;
		//temp_array = nullptr;
#ifdef DEBUG
		cout << "K" << endl;
#endif // DEBUG
	}
	//with one param - array size
	tab(unsigned int val) : size_array(new unsigned int), old_size_array(new unsigned int), array(new type), value(new type) // temp_array(new type), 
	{
		try
		{
			if (val < 0) throw 1;
			else
			{

				*size_array = val;
				*old_size_array = 0;
				array = nullptr;
				//temp_array = nullptr;
				resize(val);
			}
		}
		catch (...)
		{
			cout << "error: value exceeded (unsigned int)" << endl;
			*size_array = 1;
			*old_size_array = 0;
			array = nullptr;
			//temp_array = nullptr;
			resize(1);
		}
#ifdef DEBUG
		cout << "K2" << endl;
#endif // DEBUG
	}
	// initialize with a list 
	tab(std::initializer_list<type> lst) : size_array(new unsigned int), old_size_array(new unsigned int), array(new type), value(new type)	//lst.size()
	{
		*old_size_array = 0;
		//array = nullptr;

		//	array[*(array + *value)] = val;
		//cout << lst.end() - lst.begin() << endl;
		unsigned int temp = lst.end() - lst.begin();
		*size_array = temp;
		resize(temp);

		//cout << *lst.begin() << " " << *(lst.end()-1) << endl;
		//auto * temp_wsk = (lst.end() - 1);
		//cout << temp_wsk << " " << (lst.end()-1) << endl;
		copy(lst.begin(), lst.end(), array); // copy from lst into elem

#ifdef DEBUG
		cout << "K3" << endl;
#endif // DEBUG
	}

	/*
	Vector::Vector(std::initializer_list<double> lst) : elem{new double[lst.size()]} , sz{lst.size()}
	{
	copy(lst.begin(),lst.end(),elem); // copy from lst into elem
	}

*/
//copy-constructor
	tab(const tab& obj) : size_array(new unsigned int), old_size_array(new unsigned int), array(new type), value(new type) //, temp_array(new type)
	{
		//*size_array = 0;
		//*old_size_array = 0;
		//array = obj.array;
		//temp_array = NULL;
#ifdef DEBUG
		cout << "KK" << endl;
#endif // DEBUG
	}

	//  DESTRUCTOR
	//---------------------------	
	~tab()
	{
#ifdef DEBUG
		cout << "D" << endl;
#endif // DEBUG
		delete size_array;
		delete old_size_array;
		delete[] array;
		//delete[] temp_array;				//array == temp_array
		delete value;
	}

	//  FUNCTIONS
	//---------------------------	
	int size();
	void resize(unsigned int val);
	int count(type val);

	//  OPERATORS
	//---------------------------
	type& operator[](unsigned int val)			//array[index]
	{
		try
		{
			//if (val > 18446744073709551612)
			//throw 1;
			*value = val;
			resize(val + 1);
		}
		catch (...)
		{
			*size_array = 0;
			cout << "error: unable to create array (size is too big)" << endl;
			delete[] array;
			array = new type[0];
			//temp_array = nullptr;
			return array[0];
		}
		//cout << "array[val]: " << array[val] << " ";
		return array[val];
	}
	type& operator=(type val)								//array[index] = value
	{
		array[*(array + *value)] = val;
		return *array;
	}
	tab& operator=(const tab& obj)				//array = array
	{
		// ### Czêœæ 1) Sprawdzenie czy to nie kopiowanie siebie samego ###		
		if (&obj == this) return *this;

		// ### Czêœæ 2) "Destruktorowa"
		//delete[] array;
		//delete wsk_nazwiska;

		// ### Czêœæ 43) "Konstruktorowa (konst. kopiuj¹cy)		
			//proste przepisanie wartoœci
		*size_array = *obj.size_array;
		*old_size_array = *obj.old_size_array;
		*value = *obj.value;
		copy_array(obj.array);

		//--------------------------------------------------
		return *this;			//"referencja obiektu swojej klasy	
		//this jest wskaŸnikiem pokazuj¹cym na obiekt klasy persona, na ten konkretny,
		//na którego rzecz wywo³ano operator. Czyli ten, który postawiono po lewej stronie znaku obiekt_A = obiekt_B
	}

#ifdef WORK
	tab& operator==(tab val)
	{
		array[*(array + *value)] = val;
		return *array;
	}
	tab& operator+=(tab val)
	{
		array[*(array + *value)] += 1;
		return *array;
	}


#endif // WORK
};

#ifdef WORK
//template <class typOBJ>
//ostream& operator<<(ostream& stru, dlista<typOBJ>& spis)
#endif // WORK

//  FUNCTIONS
//---------------------------	
//size()
template<class type>
int tab<type>::size()
{
	return *size_array;
}

//resize()
template <class type>
void tab<type>::resize(unsigned int val)
{
	if (val + 1 > * size_array)
	{
		*size_array = val;
		copy_array(array);
	}
}

//count()
template<class type>
int tab<type>::count(type val)
{
	int count = 0;
	for (int i = 0; i < size_array; ++i)
	{
		if (array[i] == val)
			++count;
	}
	return count;
}

//copy_array()
template<class type>
void tab<type>::copy_array(type* wsk)
{
	//delete[] temp_array;
	unsigned int temp = *size_array;
	type* temp_array = nullptr;
	temp_array = new type[temp];
	unsigned int i;
	for (i = 0; i < *old_size_array; ++i)
		temp_array[i] = wsk[i];
	for (i = *old_size_array; i < *size_array; ++i)
		temp_array[i] = NULL;
	array = temp_array;							//!!!
	*old_size_array = *size_array;
}


/*

complex& operator+=(complex z) { re+=z.re, im+=z.im; return *this; } // add to re and im
// and return the result
complex& operator–=(complex z) { re–=z.re, im–=z.im; return *this; }
complex& operator*=(complex); // defined out-of-class somewhere
complex& operator/=(complex); // defined out-of-class somewhere

complex operator+(complex a, complex b) { return a+=b; }
complex operator–(complex a, complex b) { return a–=b; }
complex operator–(complex a) { return {–a.real(), –a.imag()}; } // unary minus
complex operator*(complex a, complex b) { return a*=b; }
complex operator/(complex a, complex b) { return a/=b; }

bool operator==(complex a, complex b) // equal
{
return a.real()==b.real() && a.imag()==b.imag();
}
bool operator!=(complex a, complex b) // not equal
{
return !(a==b);
}

For example, c!=b means operator!=(c,b) and 1/a means
operator/(complex{1},a).

*/

/*

	tab<int> a= { 1,2,3,4,5,76,8,0,7 };
	cout << endl;
	cout << a.size() << endl;

	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}


	cout << endl << endl;
	tab<int> b(2);
	cout << b.size() << endl;

	cout << endl << endl;
	tab<int> c;
	c[5] = 4;
	cout << c.size() << endl;



	cout << endl;


	*/