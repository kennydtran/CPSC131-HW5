#include <iostream>
#include <vector>

using namespace std;

// For this homework, you are going to implement an extendable vector based queue that 
// uses "jump" trick to save space. 
// Finish function 
//              front() that prints the first element in the queue
//              deque() that dequeues the queue
//          	enque(val) that enqueues val to the queue
//              print_vect() that prints out vect_que.
// Demonstrate that your code works in main.
// Refer to class PPT if you forgot all the different cases.

template <class T>

class vect_queue {
    vector<T> vect_que;
    size_t size_;
    int que_front_;
    int que_back_;

public:
    vect_queue<T>(T val) {
        vect_que.push_back(val);
        size_ = 1;
        que_front_ = 0;
        que_back_ = 0;
    }

    int map(int i) {
        int j = 0;

        if (vect_que.size() != 0) {
            if (que_front_ + i < vect_que.size()) {
                j = i + que_front_;
            } else {
                j = i + que_front_ - vect_que.size();
            }
        }
        return j;
    }

    T front() const {
        return vect_que[que_front_];
    }
    T back() const {
        return vect_que[que_back_];
    }

    void deque() {
        if (size_ > 1) {
            size_--;
            vect_que[que_front_] = NULL;
            if (que_front_ == vect_que.size() - 1) {
                que_front_ = 0;
            } else {
                que_front_++;
            }
        } else if (size_ == 1) {
            size_--;
            vect_que[que_front_] = NULL;
            que_front_ = 0;
            que_back_ = 0;
        } else {
            cout << "Error: Cannot deque in an empty queue" << "\n\n";
        }

    }

    void enque(T val) {
        if (size_ < vect_que.size()) {
            if (size_ == 0) {
                size_++;
                vect_que[que_front_] = val;
            } else {
                size_++;
                if (que_back_ != vect_que.size() - 1) {
                    vect_que[que_back_ + 1] = val;
                    que_back_++;
                } else {
                    vect_que[0] = val;
                    que_back_ = 0;
                }
            }
        } else if (size_ == vect_que.size()) {
            vector<T> vect_que2;
            if (vect_que.size() > 0) {
                vect_que2.resize(vect_que.size() * 2);
                for (int i = 0; i < size_; i++) {
                    vect_que2[que_front_ + i] = vect_que[map(i)];
                }

                vect_que2[que_front_ + size_] = val;
                que_back_ = que_front_ + size_;
                vect_que = vect_que2;
                size_++;
            } else {
                vect_que2.resize(1);
                vect_que2.push_back(val);
                que_back_ = 1;
                vect_que = vect_que2;
                size_++;
            }
        } else {
            cout << "Error: size cannot exceed capacity" << "\n\n";
        }
    }

    void print_vect() const {
        for (int i = 0; i < vect_que.size(); i++) {
            cout << vect_que[i] << " ";
        }
        cout << "\nFront: " << que_front_;
        cout << " Back: " << que_back_ << endl;
    }
};

int main() {
    //Demonstrate your code works by adding/removing values in a vect_que class 
    //object. Print out your result.
    //You should include front index of queue, back index of queue, and the entire
    //vector (not queue) for each case.

    //case 1: add to an empty queue
    cout << "Case 1" << endl;
    vect_queue<int> test(1);
    test.deque();
    test.print_vect();
    test.enque(1);
    test.print_vect();
    cout << endl << endl;


    //case 2: add to a non-empty queue without jump
    cout << "Case 2" << endl;
    test.print_vect();
    test.enque(2);
    test.print_vect();
    cout << endl << endl;


    //case 3: add to a non-empty queue with a jump
    cout << "Case 3" << endl;
    test.deque();
    test.print_vect();
    test.enque(3);
    test.print_vect();
    cout << endl << endl;


    //case 4: remove from a queue with number of elements > 1 
    //        and que.front not at vect.back
    cout << "Case 4" << endl;
    test.deque();
    test.deque();
    test.enque(3);
    test.enque(2);
    test.print_vect();
    test.deque();
    test.print_vect();
    cout << endl << endl;


    //case 5: remove from a queue with number of elements > 1 
    //        and que.front at vect.back
    cout << "Case 5" << endl;
    test.enque(3);
    test.print_vect();
    test.deque();
    test.print_vect();
    cout << endl << endl;


    //case 6: remove from a queue with 1 element in it and que.front 
    //        not at vect[0]
    cout << "Case 6" << endl;
    test.enque(4);
    test.deque();
    test.print_vect();
    test.deque();
    test.print_vect();
    cout << endl;

    cout << "\nprogram ends here.\n";

    return 0;
}