#include <future>
#include <algorithm>



template <typename RandomIt, typename Func>
void parallel_for_each(RandomIt beg, RandomIt end, Func func) {
	

	//T result = 0;
	int len = end - beg;
	if (len < 3) {
		std::for_each(beg, end, *func);
		return;
	}
		

	RandomIt mid = beg + len / 2;
	std::future<void> handle = std::async(std::launch::async, parallel_for_each<RandomIt, Func>, mid, end, func);
	parallel_for_each<RandomIt, Func>(beg, mid, func);
	handle.wait();
	return;
	
	//std::cout << "The sum is " << result_first_half + handle.get() << '\n';
}

