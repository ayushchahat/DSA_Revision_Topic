class Solution {
public:
    bool isPal(string s) {
        int l = 0;
        int h = s.size() - 1;

        while (l < h) {
            if (s[l] != s[h]) {
                return false;
            }
            l++;
            h--;
        }
        return true;
    }

    void solve(int i, int n, string str,
               vector<string>& res,
               vector<vector<string>>& ans,
               string& s) {

        if (i == n) {
            if (!str.empty() && isPal(str)) {
                res.push_back(str);
                ans.push_back(res);
                res.pop_back();
            }
            return;
        }

        str += s[i];

        // Choice 1: Cut here
        if (isPal(str)) {
            res.push_back(str);

            solve(i + 1, n, "", res, ans, s);

            res.pop_back();
        }

        // Choice 2: Don't cut, extend substring
        solve(i + 1, n, str, res, ans, s);
    }

    vector<vector<string>> partition(string s) {
        int n = s.size();

        vector<vector<string>> ans;
        vector<string> res;

        solve(0, n, "", res, ans, s);

        return ans;
    }
};