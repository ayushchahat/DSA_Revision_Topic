class Solution {
public:
    int ladderLength(string beginWord, string endWord,
                     vector<string>& wordList) {

        unordered_set<string> st(wordList.begin(), wordList.end());

        // If endWord is not present, transformation is impossible.
        if (st.find(endWord) == st.end()) {
            return 0;
        }

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        // Mark beginWord as visited by removing it from the set.
        st.erase(beginWord);

        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            // BFS guarantees this is the shortest sequence.
            if (word == endWord) {
                return steps;
            }

            // Change each character one by one.
            for (int i = 0; i < word.size(); i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    if (ch == original) {
                        continue;
                    }

                    word[i] = ch;

                    // Check whether the transformed word exists.
                    if (st.find(word) != st.end()) {
                        q.push({word, steps + 1});

                        // Remove immediately to avoid revisiting.
                        st.erase(word);
                    }
                }

                // Restore the original character.
                word[i] = original;
            }
        }

        return 0; // No transformation sequence exists.
    }
};