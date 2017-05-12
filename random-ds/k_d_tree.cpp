#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

template <size_t N>
class Point {
    vector<double> coordinates;

    public:

    Point(){
        coordinates.resize(N);
    }

    double& operator[](int idx){
        return coordinates[idx];
    }

    const double& operator[](int idx) const {
        return coordinates[idx];
    }

    bool operator == (const Point &point) const { 
        for (int i = 0; i < N; i++) {
            if ((this->coordinates)[i] != point[i]) {
                return false;
            }
        }
        return true;
    }
};

template <size_t N, class ValueType>
class KDTree
{
    struct Node {
        Point<N> point;
        ValueType value;
        Node *left;
        Node *right;

        Node(const Point<N> &point, const ValueType &value): point(point), value(value)
        {
            left = right = NULL;
        }
    };

    double EuclidDist(const Point<N> &a, const Point<N> &b){
        double dist = 0;
        for (int i = 0; i < N; i++) {
            dist += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return pow(dist, 0.5);
    }

    Node* root;

    Node *insertPoint(Node *subTreeRoot, const Point<N> &point, const ValueType &value, int keyedOn){
        if (subTreeRoot == NULL) {
            return new Node(point, value);
        }
        if (subTreeRoot->point == point) {
            subTreeRoot->value = value;
            return subTreeRoot;
        }
        int nextKeyedOn = (keyedOn == N-1)? 0: keyedOn + 1;
        if (point[keyedOn] < (subTreeRoot->point)[keyedOn]) {
            subTreeRoot->left = insertPoint(subTreeRoot->left, point, value, nextKeyedOn);
        } else {
            subTreeRoot->right = insertPoint(subTreeRoot->right, point, value, nextKeyedOn);
        }
        return subTreeRoot;
    }

    Node *findPoint(Node *subTreeRoot, const Point<N> &point, int keyedOn){
        if (subTreeRoot == NULL) {
            return NULL;
        }
        int nextKeyedOn = (keyedOn == N-1)? 0: keyedOn + 1;
        if (point == subTreeRoot->point) {
            return subTreeRoot;
        } else if (point[keyedOn] < subTreeRoot->point[keyedOn]) {
            return findPoint(subTreeRoot->left, point, nextKeyedOn);
        } else {
            return findPoint(subTreeRoot->right, point, nextKeyedOn);
        }
        return subTreeRoot;
    }

    void NNSearchPoint(Node *subTreeRoot, const Point<N> &testPoint, Point<N> &candPoint, double &minDist, int keyedOn){
        if (subTreeRoot == NULL) {
            return;
        }
        if (EuclidDist(subTreeRoot->point, testPoint) < minDist) {
                candPoint = subTreeRoot->point;
                minDist = EuclidDist(subTreeRoot->point, testPoint);
        }
        int nextKeyedOn = (keyedOn == N-1)? keyedOn + 1: 0;
        if (testPoint[keyedOn] < (subTreeRoot->point)[keyedOn]) {
            NNSearchPoint(subTreeRoot->left, testPoint, candPoint, minDist, nextKeyedOn);
            if (testPoint[keyedOn] - (subTreeRoot->point)[keyedOn] <= minDist) {
                NNSearchPoint(subTreeRoot->right, testPoint, candPoint, minDist, nextKeyedOn);
            }
        } else {
            NNSearchPoint(subTreeRoot->right, testPoint, candPoint, minDist, nextKeyedOn);
            if ((subTreeRoot->point)[keyedOn] - testPoint[keyedOn] <= minDist) {
                NNSearchPoint(subTreeRoot->left, testPoint, candPoint, minDist, nextKeyedOn);
            }
        }
    }

    public:

    KDTree(){
        root = NULL;
    }

    void insert(const Point<N> point, const ValueType value) {
        root = insertPoint(root, point, value, 1);
    }

    bool contains(const Point<N> point) {
        return (findPoint(root, point, 1) != NULL)? 1: 0;
    }

    ValueType& operator[] (const Point<N> &point const){
        return findPoint(root, point, 1)->value;
    }

    Point<N> NNSearch (const Point<N> testPoint){
        double minDist = EuclidDist(root->point, testPoint);
        NNSearchPoint(root, testPoint, candPoint, minDist, 1);
        return candPoint;
    }
};

int main(){
    KDTree<2, int> T;
}
