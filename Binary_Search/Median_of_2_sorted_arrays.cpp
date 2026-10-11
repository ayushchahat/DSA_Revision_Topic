class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int n1 = a.size(), n2 = b.size();

        if (n1 > n2)
            return findMedianSortedArrays(b, a);

        int n = n1 + n2;
        int k = (n + 1) / 2;

        int l = max(0, k - n2);
        int h = min(k, n1);

        while (l <= h) {
            int mid = l + (h - l) / 2;
            int bMid = k - mid;

            int al = mid == 0 ? INT_MIN : a[mid - 1];
            int ar = mid == n1 ? INT_MAX : a[mid];

            int bl = bMid == 0 ? INT_MIN : b[bMid - 1];
            int br = bMid == n2 ? INT_MAX : b[bMid];

            if (al <= br && bl <= ar) {
                if (n % 2 == 1)
                    return max(al, bl);

                return ((double)max(al, bl) + min(ar, br)) / 2.0;
            }
            else if (al > br) {
                h = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }

        return -1;
    }
};