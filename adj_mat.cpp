#include "adj_mat.h"

adj_mat::adj_mat(int graphsz)
{
 mat.resize(graphsz);
 for(int i = 0; i<graphsz; ++i )
     mat[i].resize(graphsz);


}

int adj_mat::add_vertex(){
    mat.resize(mat.size()+1);
    for(int i = 0; i<mat.size(); ++i )
        mat[i].resize(mat.size());
    return mat.size()-1;
}

void adj_mat::delete_vertex(int ind){
    mat.erase(mat.begin()+ind);
    for(int i = 0; i<mat.size(); ++i ){
        mat[i].erase(mat[i].begin()+ind);
        }

}

void adj_mat::connect_nodes(int ind1, int ind2, int price){
        if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size() && price>0){
                mat[ind1][ind2] = price;
            }
}


void adj_mat::disconnect_nodes(int ind1, int ind2){
        if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
                mat[ind1][ind2] = 0;
            }
}



void adj_mat::connect_nodes_tw(int ind1, int ind2, int price){
        if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size() && price>0){
                mat[ind1][ind2] = price;
                mat[ind2][ind1] = price;
            }
}

void adj_mat::disconnect_nodes_tw(int ind1, int ind2){
        if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
                mat[ind1][ind2] = mat[ind2][ind1] = 0;
            }
}

int adj_mat::price(int ind1, int ind2){
    if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
           return  mat[ind1][ind2];
        }
    return -1;
}

void adj_mat::set_price(int ind1, int ind2, int price){
    if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
           mat[ind1][ind2] = price;
        }
}

void adj_mat::set_price_tw(int ind1, int ind2, int price){
    if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
           mat[ind1][ind2] = mat[ind2][ind1] =  price;
        }
}


int adj_mat::max_price(int ind, int& max_ind){
   int max = -1;
    if( ind >= 0 && ind < mat.size())
        {
            max = 0;
            for(int i = 0; i<mat.size(); ++i)
                if(mat[ind][i] >max){
                        max = mat[ind][i];
                        max_ind = i;
                    }
        }
    return max;
}

int adj_mat::min_price(int ind, int& min_ind){
   int max = -1;
    if( ind >= 0 && ind < mat.size())
        {
            if(mat.size()>0)
                max = mat[ind][ind];
            for(int i = 0; i<mat.size(); ++i)
                if(mat[ind][i] < max && mat[ind][i] > 0){
                        max = mat[ind][i];
                        min_ind = i;
                    }
        }
    return max;
}

int adj_mat::size(){
   return mat.size();
}

 bool adj_mat::is_path(int ind1, int ind2, const std::set<int>& S){
     bool visited[size()];
     if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){


             if(mat[ind1][ind2] > 0 ){
                 if(S.find(ind2) != S.end())
                    return true;
                 else return false;}


             visited[ind1] = true;
             std::queue<int> q;
             for(int i = 0; i<size(); ++i){
                     if(S.find(i) != S.end() && mat[ind1][i]>0 && visited[i] != true)
                         q.push(i);
                 }

             while(!q.empty()){
                     int ind  = q.back();
                     q.pop();
                     for(int i = 0; i<size(); ++i){
                             if(S.find(i) != S.end() && mat[ind][i]>0 && visited[i] != true){
                                 if(i == ind2)
                                     return true;
                                  else{
                                        q.push(i);
                                        visited[ind] = true;
                                     }
                                 }
                         }
                 }


         }
     return false;
 }

 bool adj_mat::is_path(int ind1, int ind2){
     bool visited[size()];
     if( ind1 >= 0 && ind2>=0 && ind1 < mat.size() && ind2 < mat.size()){
             if(mat[ind1][ind2] > 0 )
                    return true;


             visited[ind1] = true;
             std::queue<int> q;
             for(int i = 0; i<size(); ++i){
                     if( mat[ind1][i]>0 && visited[i] != true)
                         q.push(i);
                 }

             while(!q.empty()){
                     int ind  = q.back();
                     q.pop();
                     for(int i = 0; i<size(); ++i){
                             if(mat[ind][i]>0 && visited[i] != true){
                                 if(i == ind2)
                                     return true;
                                  else{
                                        q.push(i);
                                        visited[ind] = true;
                                     }
                                 }
                         }
                 }

         }
    return false;
   }



adj_mat MST(adj_mat& mat){
    /// set of vertexes
    std::vector< std::pair< std::pair<int, int>, int>> S;
    for(int i = 0; i<mat.size(); ++i)
        for(int j = 0; j<mat.size(); ++j)
            if(mat.price(i,j) > 0)
                S.push_back({{i,j},mat.price(i,j)});

    /// sort by inc
    std::sort(S.begin(),S.end(),[](const std::pair< std::pair<int, int>, int>& p1,const std::pair< std::pair<int, int>, int>& p2 )->bool{ return p1.second<p2.second; });

    /// forest
    adj_mat mst(mat.size());

    while(!S.empty() ){
            // copy min edge
            std::pair< std::pair<int, int>,int> edge = *S.begin();
            // delete it from edge set
            S.erase(S.begin());
            /// if edge creates a cycle in mst <==> there is a path in mst from edge's destination to its beginning than screw it
            if(!mst.is_path(edge.first.second,edge.first.first))
                // else add it to mst
                    mst.connect_nodes(edge.first.first,edge.first.second,edge.second);

        }
    return mst;
}


