/**
 * Description: Monotone Priority Queues (Supports sliding window queries)   
 * Usage: pushmax, pushmin, O(N)  
 * Source: https://github.com/dragonslayerx 
 */

deque<int> maxq, minq;
void pushmax(int element) {
    while (!maxq.empty() && element > maxq.back()) maxq.pop_back();
    maxq.push_back(element);
}


void pushmin(int element) {
    while (!minq.empty() && element < minq.back()) minq.pop_back();
    minq.push_back(element);
}
