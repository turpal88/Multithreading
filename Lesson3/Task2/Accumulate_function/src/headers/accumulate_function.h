#include <numeric>

template<class It, class T>
T accumulate_function(It begin, It end){
	
	return std::accumulate(begin, end, 0);
}