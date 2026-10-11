class Solution {
public:
    int kthElement(vector<int> &a, vector<int>& b, int k) {
        int n1 = a.size();
        int n2 = b.size();

        if (n1 > n2)
            return kthElement(b, a, k);

        int l = max(0, k - n2);
        int h = min(k, n1);

        while (l <= h) {
            int mid = l + (h - l) / 2;
            int bMid = k - mid;

            int aLeft = (mid == 0) ? INT_MIN : a[mid - 1];
            int aRight = (mid == n1) ? INT_MAX : a[mid];

            int bLeft = (bMid == 0) ? INT_MIN : b[bMid - 1];
            int bRight = (bMid == n2) ? INT_MAX : b[bMid];

            if (aLeft <= bRight && bLeft <= aRight) {
                return max(aLeft, bLeft);
            }
            else if (aLeft > bRight) {
                h = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }

        return -1;
    }
};