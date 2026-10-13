class Solution {
public:
    bool solve(int r,int c,int k,int m,int n,int t,vector<vector<int>> &vis,vector<vector<char>>& board, string &word){
        if(k==t){
            return true;
        }
        vis[r][c]=1;
        int dr[4]={0,1,0,-1};
        int dc[4]={1,0,-1,0};
        for(int i=0;i<4;i++){
            int nr=r+dr[i];
            int nc=c+dc[i];
            if(nr>=0 && nr<m && nc>=0 && nc<n && !vis[nr][nc] && board[nr][nc]==word[k]){
                if(solve(nr,nc,k+1,m,n,t,vis,board,word)){
                    return true;
                }
            }
        }
        vis[r][c]=0;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();
        int t=word.size();
        vector<pair<int,int>> start;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]==word[0]){
                    start.push_back({i,j});
                }
            }
        }
        vector<vector<int>> vis(m,vector<int>(n,0));
        for(int i=0;i<start.size();i++){
            int sr=start[i].first;
            int sc=start[i].second;
            if(solve(sr,sc,1,m,n,t,vis,board,word)){
                return true;
            }
        }
        return false;
    }
};