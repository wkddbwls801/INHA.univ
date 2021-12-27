# pandas

Created: December 20, 2021 4:32 PM

# 요구사항

---

- 가장 인기 있는 100대 영화 목록을 만드세요.
    
    가. 전체 이용자의 1) 성별 2) 직업별 3) 평점이 많은 순서대로 영화 목록을 추출한다.
    
    나. 전체 이용자의 1) 성별 2) 직업별 3) 평균 평점이 가장 높은 영화 목록을 추출합니다.
    
- 장르별로 등급을 계산합니다.
    
    가. 1) 모든 사용자, 2) 성별, 3) 모든 직업에 대한 장르별 시청률을 집계하여 내림차순으로 분류한다.
    
    나. 장르별 평균 시청률 측정
    

# 기초 개념 공부

## 1. csv 파일 불러오기 : read_csv()

---

```python
import pandas as pd
csv_test = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.item')
```

## 2. 구분자 설정하기 : sep = '|'

---

```python
csv_test = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.item', sep = '|')
```

- 구분자가 '|' 이면 `sep = '|'` 으로 적어주고, 구분자가 탭(tab)이면 `sep = '\t'`로 적어주면 된다.

## 3. 변수 이름(column name, header)이 없는 파일 불러올 때 이름 부여하기 : names=['X1', 'X2', ...]

---

```python
csv_test = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.user', sep= "|", names=['user id', 'age', 'gender', 'occupation', 'zip code'])
```

## 4. 유니코드 디코드 에러, UnicodeDecodeError : 'utf-8' codec can't decode byte

---

- 불러오는 text, csv 파일의 encoding 설정과 Python encoding 설정이 서로 맞지 않으면 UnicodeDecodeError가 발생한다.
- UTF-8로 encoding된 파일들은 잘 불러와졌으나, ANSI로 encoding되어 저장된 파일은 위의 문제가 발생하였다.
- 여러 구글링을 통해 다양한 방법을 얻을 수 있었다.
    - `encoding='CP949'`
    - `encoding='latin'`
    - `encoding='utf-8'`
    - `engine='python'`
    
    ⇒ 다양한 방법을 시도하였으나 결국에는 engine='python'를 작성하여 해결할 수 있었다.
    

## 5. 두 개의 dataframe 합치기 : merge()

- `merge()` 함수는 두 데이터 프레임을 각 데이터에 존재하는 고유값(key)을 기준으로 병합할 때 사용한다.
- `pd.merge(df_left, de_right, how='inner', on=None)`이  default이다.
    
    ```python
    user_dataframe = pd.merge(user_data, rating_data, how='outer', on='user id')
    ```
    
- `how='outer'` 옵션은 어느 한 쪽에라도 없는 데이터가 있는 경우 NaN값이 지정된다.

## 6. 특정 행, 열 삭제하기 : drop()

- `drop()` 함수를 통해 원하는 행 또는 열을 삭제할 수 있다.
- `axis = 0`은 dataframe  행 단위를 수정할 때 필요한 파라미터 값이다.
- `axis = 1`은 dataframe 열 단위를 수정할 때 필요한 파라미터 값이다.
    
    ```python
    user_dataframe = pd.merge(user_data, rating_data, how='outer', on='user id').drop(['age','zip code','timestamp'], axis='columns')
    ```
    
    - 열 단위를 수정할 때 `axis = 1` 대신에 `axis = 'colums'`로 적어도 상관없다.

## 7. 그룹별로 집계하기 : groupby()

- `groupby()`는 같은 값을 하나로 묶어 통계 또는 집계 결과를 얻기 위해 사용된다.
- `mean()` 함수는 평균을 구할 때 사용된다.
- `sum()` 함수는 합을 구할 때 사용된다.
- `size()` 함수는 개수를 알고 싶을 때 사용한다.
    
    ```python
    rating_by_user = user_in_movie_dataframe['rating'].groupby(user_in_movie_dataframe['movie id']).size()
    ```
    
    - `user_in_movie_dataframe`의 `rating`을 `movie id`로 그룹화 한 후, `rating`의 개수를 알고 싶을 때 사용하는 코드이다. ⇒ 영화 별 평점의 개수를 알 수 있다.

# 코드 분석

### 1. 가장 인기 있는 100대 영화 목록을 만드세요.

- **<data 추출>**
    
    ```python
    import pandas as pd
    import numpy as np
    from pandas import Series, DataFrame
    
    # 영화 정보
    movies_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.item', sep="|", names=['movie id', 'movie title', 'release date', 'video release date', 'IMDb URL', 'unknown', 'Action', 'Adventure', 'Animation', "Children's", 'Comedy', 'Crime', 'Documentary', 'Drama', 'Fantasy', 'Film-Noir', 'Horror', 'Musical', 'Mystery', 'Romance', 'Sci-Fi', 'Thriller', 'War', 'Western'], engine='python')
    
    # 사용자 정보
    user_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.user', sep= "|", names=['user id', 'age', 'gender', 'occupation', 'zip code'])
    
    # 평점 정보
    rating_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.data', sep="\t", names=['user id', 'movie id', 'rating', 'timestamp'])
    
    # 사용자의 직업 리스트
    user_occupation_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.occupation', names=['occupation'])
    
    # 영화 정보 = 영화 id, 영화 title => 2차원 배열
    movies_df = movies_data[['movie id', 'movie title']]
    
    # 사용자 별 평점
    user_dataframe = pd.merge(user_data, rating_data, how='outer', on='user id').drop(['age','zip code','timestamp'], axis='columns')
    
    # 사용자 별 영화 평점 정보 - 사용자 id, 성별, 직업, 영화 id, 평점, 영화 제목
    user_in_movie_dataframe = pd.merge(user_dataframe, movies_df, how='outer', on='movie id')
    print(user_in_movie_dataframe)
    ```
    
    - `movies_df`를 2차원 배열로 설정한 이유는 뒤쪽에서 movie id로 정렬을 하여 알맞은 title을 고를 수 있도록 하기 위해서이다. `movies_df.values`를 하면 2차원 배열로 movie id와 title이 한 묶음인 2차원 배열이 출력된다. `movies_df.values[0][0]`을 출력하면 ‘Toy Story (1995)`의 movie id인 1이 출력이 된다.
        
        ```
        [[1 'Toy Story (1995)']
         [2 'GoldenEye (1995)']
         [3 'Four Rooms (1995)']
         ...
         [1680 'Sliding Doors (1998)']
         [1681 'You So Crazy (1994)']
         [1682 'Scream of Stone (Schrei aus Stein) (1991)']]
        ```
        

- **<사용자 별 평점>**
    
    ```python
    # 사용자 별 평점
    
    rating_by_user = movies_df['movie title'][user_in_movie_dataframe['rating'].groupby(user_in_movie_dataframe['movie id']).size().sort_values(ascending=False)[:100].index-1]
    
    arr = np.array([])
    
    for n in rating_by_user:
        arr = np.append(arr, n)
    
    dic = {'title' : arr}
    result = pd.DataFrame(dic, index=range(1, 101))
    result.index.name='rank'
    
    result
    ```
    
    - `rating_by_user` 변수는 `movi id` 별로 `rating`의 개수를 알아 내었고, 그 개수들의 index 즉, `movie id`를 `movie title`과 매칭시켜서 평점이 많은 상위 100개의 영화를 추출할 수 있었다.
    - index - 1을 한 이유는, `movie title`의 index가 0부터 시작하기 위해 알맞게 매칭을 시키기 위해 -1을 하였다. 이후, `rating_by_user`를 출력해보면 `movie id`가 원래의 값보다 1씩 줄어든 것을 알 수 있다.(정상적인 것임)
    - 위의 출력을 index가 `movie id`가 아닌 `rank`로 표현하기 위해 `numpy`를 사용하였다. `array`에 `rating_by_user` 변수의 values 값 즉, `movie title`을 넣고, 다시 표 형태로 표현하였다.
    
- **<사용자 성별 별 평점>**
    
    ```python
    # 사용자 성별 별 평점
    movie_by_man = user_in_movie_dataframe[user_in_movie_dataframe['gender'] == 'M']
    movie_by_woman = user_in_movie_dataframe[user_in_movie_dataframe['gender'] == 'F']
    
    rating_by_man = movies_df['movie title'][movie_by_man['rating'].groupby(movie_by_man['movie id']).size().sort_values(ascending=False)[:100].index-1]
    rating_by_woman = movies_df['movie title'][movie_by_woman['rating'].groupby(movie_by_woman['movie id']).size().sort_values(ascending=False)[:100].index-1]
    
    arr_man = np.array([])
    arr_woman = np.array([])
    
    for n in rating_by_man:
        arr_man = np.append(arr_man, n)
    
    for n in rating_by_woman:
        arr_woman = np.append(arr_woman, n)
        
    dic = {'man' : arr_man, 'woman' : arr_woman}
    
    result = pd.DataFrame(dic, index = range(1, 101))
    result.index.name='rank'
    result
    ```
    
    - `movie_by_man` 변수에는 남성의 정보만, `movie_by_woman`의 정보에는 여성의 정보만을 담았다. 위의 방식과 동일하게 `rating_by_man`, `rating_by_woman`의 정보를 얻어낸 후, `numpy`의 `array`에 담았다.

- **<사용자 직업 별 평점>**
    
    ```python
    # 사용자 직업 별 평점
    dic={}
    
    for job in user_occupation_data['occupation'].values:
        movie_by_occupation = user_in_movie_dataframe[user_in_movie_dataframe['occupation'] == job]
        
        rating_by_occupation = movies_df['movie title'][movie_by_occupation['rating'].groupby(movie_by_occupation['movie id']).size().sort_values(ascending=False)[:100].index-1]
        
        arr_occupation = np.array([])
        
        for n in rating_by_occupation:
            arr_occupation = np.append(arr_occupation, n)
            
        dic[job] = arr_occupation
    
    result = pd.DataFrame(dic, index = range(1, 101))
    result.index.name='rank'
    result
    ```
    
    - `user_occupation_data`에 있는 values 즉, 직업의 수 만큼 `for문`을 돌면서 `movie_by_occupation` 변수에 사용자의 정보와 영화의 정보가 같이 담겨 있는 `user_in_movie_dataframe` 변수에서의 직업과 일치하는 정보를 담는다. 이후, 앞선 방법과 같이 평점이 많은 순서대로 `movie title`을 얻은 후, `array`에 담았다.

- **< 사용자 별 평균 평점>**
    
    ```python
    # 사용자 별 평균 평점
    rating_by_user = movies_df['movie title'][user_in_movie_dataframe['rating'].groupby(user_in_movie_dataframe['movie id']).mean().sort_values(ascending=False)[:100].index-1]
    
    arr = np.array([])
    
    for n in rating_by_user:
        arr = np.append(arr, n)
    
    dic = {'title' : arr}
    result = pd.DataFrame(dic, index=range(1, 101))
    result.index.name='rank'
    
    result
    ```
    
    - 앞서 평점을 구할 때는 `size()` 함수를 사용하였으나, 평균을 구하고 싶을 때는 `mean()` 함수를 사용하면 된다.

- **< 사용자 성별 별 평균 평점>**
    
    ```python
    # 사용자 성별 별 평균 평점
    movie_by_man = user_in_movie_dataframe[user_in_movie_dataframe['gender'] == 'M']
    movie_by_woman = user_in_movie_dataframe[user_in_movie_dataframe['gender'] == 'F']
    
    rating_by_man = movies_df['movie title'][movie_by_man['rating'].groupby(movie_by_man['movie id']).mean().sort_values(ascending=False)[:100].index-1]
    rating_by_woman = movies_df['movie title'][movie_by_woman['rating'].groupby(movie_by_woman['movie id']).mean().sort_values(ascending=False)[:100].index-1]
    
    arr_man = np.array([])
    arr_woman = np.array([])
    
    for n in rating_by_man:
        arr_man = np.append(arr_man, n)
    
    for n in rating_by_woman:
        arr_woman = np.append(arr_woman, n)
        
    dic = {'man' : arr_man, 'woman' : arr_woman}
    
    result = pd.DataFrame(dic, index = range(1, 101))
    result.index.name='rank'
    result
    ```
    
    - `mean()` 함수를 사용하였다.
    
- **< 사용자 직업 별 평균 평점>**
    
    ```python
    # 사용자 직업 별 평균 평점
    #occupation_len = user_occupation_data['occupation'].values.size
    
    dic={}
    
    for job in user_occupation_data['occupation'].values:
        movie_by_occupation = user_in_movie_dataframe[user_in_movie_dataframe['occupation'] == job]
        
        rating_by_occupation = movies_df['movie title'][movie_by_occupation['rating'].groupby(movie_by_occupation['movie id']).mean().sort_values(ascending=False)[:100].index-1]
        
        arr_occupation = np.array([])
        
        for n in rating_by_occupation:
            arr_occupation = np.append(arr_occupation, n)
            
        dic[job] = arr_occupation
    
    result = pd.DataFrame(dic, index = range(1, 101))
    result.index.name='rank'
    result
    ```
    
    - `mean()` 함수를 사용하였다.

### 2. 장르별로 등급을 계산합니다.

- **< 데이터 추출>**
    
    ```python
    import pandas as pd
    import numpy as np
    from pandas import Series, DataFrame
    
    # 3번 문제
    
    # 영화 정보
    movies_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.item', sep="|", names=['movie id', 'movie title', 'release date', 'video release date', 'IMDb URL', 'unknown', 'Action', 'Adventure', 'Animation', "Children's", 'Comedy', 'Crime', 'Documentary', 'Drama', 'Fantasy', 'Film-Noir', 'Horror', 'Musical', 'Mystery', 'Romance', 'Sci-Fi', 'Thriller', 'War', 'Western'], engine='python')
    
    # 사용자 정보
    user_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.user', sep= "|", names=['user id', 'age', 'gender', 'occupation', 'zip code'])
    
    # 평점 정보
    rating_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.data', sep="\t", names=['user id', 'movie id', 'rating', 'timestamp'])
    
    # 사용자의 직업 리스트
    user_occupation_data = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.occupation', names=['occupation'])
    
    # 영화 장르
    movie_genre = pd.read_csv('E:/#개인공부/crawling/m1-100k/u.genre', sep='|', names=['genre', 'value'])
    
    # 영화 정보 중 장르만 추출 -> 영화 id, 장르 종류..
    movies_df = movies_data.drop(['movie title', 'release date', 'video release date', 'IMDb URL'], axis='columns')
    
    # 사용자 별 평점 -> 사용자 id, 성별, 직업, 영화 id, 평점
    user_dataframe = pd.merge(user_data, rating_data, how='outer', on='user id').drop(['age','zip code','timestamp'], axis='columns')
    
    # 사용자 정보 + 장르 정보 -> 사용자 id, 성별, 직업, 영화 id, 평점, 장르 종류
    user_in_genre_dataframe = pd.merge(user_dataframe, movies_df, how='outer', on='movie id')
    ```
    
    - 장르별로 영화 순위를 매겨야 하므로 장르 정보를 얻어와 `movie genre` 변수에 저장한다.
    
- **<사용자에 대한 장르별 평점>**
    
    ```python
    # 모든 사용자에 대한 장르 별 시청률
    
    temp_dic={}
    
    for g in movie_genre['genre'].values:
        temp_dic[g] = user_in_genre_dataframe[user_in_genre_dataframe[g] == 1]['rating'].size
        
    temp = pd.Series(temp_dic).sort_values(ascending=False)
    
    arr1 = np.array([])
    arr2 = np.array([])
    
    for n in temp.index:
        arr1 = np.append(arr1, n)
    
    for n in temp.values:
        arr2 = np.append(arr2, n)
    
    dic={'genre' : arr1, 'rating' : arr2}
    
    result = pd.DataFrame(dic, index=range(1, 20))
    result.index.name='rank'
    
    result
    ```
    
    - 사용자 정보와 장르 정보, 영화 정보를 모두 담고 있는 `user_in_genre_dataframe` 변수에서 해당 장르의 값이 1인 것의 `rating`의 개수를 `temp_dic[g]` 에 담았다. 이 `directory`를 `Series`로 변환하여 `array` 배열에 다시 담아 출력한다.
    
- **< 사용자 성별에 대한 장르별 평점>**
    
    ```python
    # 성별에 따른 장르 별 시청률 집계
    
    genre_by_man = user_in_genre_dataframe[user_in_genre_dataframe['gender'] == 'M']
    genre_by_woman = user_in_genre_dataframe[user_in_genre_dataframe['gender'] == 'F']
    
    dic_man = {}
    dic_woman = {}
    
    for g in movie_genre['genre'].values:
        dic_man[g] = genre_by_man[genre_by_man[g] == 1]['rating'].size
        dic_woman[g] = genre_by_woman[genre_by_woman[g] == 1]['rating'].size
    
    temp_man = pd.Series(dic_man).sort_values(ascending=False)
    temp_woman = pd.Series(dic_woman).sort_values(ascending=False)
    
    arr1 = np.array([])
    arr2 = np.array([])
    arr3 = np.array([])
    arr4 = np.array([])
    
    for n in temp_man.index:
        arr1 = np.append(arr1, n)
    
    for n in temp_woman.index:
        arr2 = np.append(arr2, n)
        
    for n in temp_man.values:
        arr3 = np.append(arr3, n)
    
    for n in temp_woman.values:
        arr4 = np.append(arr4, n)
    
    dic_man={"Man's Genre" : arr1, "Man's Rating" : arr3}
    dic_woman={"Woman's Genre" : arr2, "Woman's Rating" : arr4}
    
    result_man = pd.DataFrame(dic_man, index = range(1,20))
    result_woman = pd.DataFrame(dic_woman, index = range(1,20))
    
    result = pd.concat([result_man, result_woman], axis=1)
    
    result
    ```
    
    - `genre_by_man`, `genre_by_woman` 변수에 각각 `user_in_genre_dataframe` 변수에서의 남성의 정보, 여성의 정보를 담는다. 이후, 앞선 방법과 동일하게 성별 별 `directory`를 각각 만든 후, 마지막에 `concat()` 함수를 통해서 하나의 `array`로 합친다.
    
- **<사용자 직업에 따른 장르별 평점>**
    
    ```python
    # 직업에 따른 장르 별 평점
    
    dic = {}
    
    for job in user_occupation_data['occupation'].values:
        genre_by_occupation = user_in_genre_dataframe[user_in_genre_dataframe['occupation'] == job]
        
        for g in movie_genre['genre'].values:
            dic[g] = genre_by_occupation[genre_by_occupation[g] == 1]['rating'].size
        
        temp = pd.Series(dic).sort_values(ascending=False)
    
    arr1 = np.array([])
    arr2 = np.array([])
    
    for n in temp.index:
        arr1 = np.append(arr1, n)
    
    for n in temp.values:
        arr2 = np.append(arr2, n)
    
    dic={'genre' : arr1, 'rating' : arr2}
    
    result = pd.DataFrame(dic, index=range(1, 20))
    result.index.name='rank by occupation'
    
    result
    ```
    
    - `user_occupation_data` 변수에서의 `occupation` 의 내용을 가지고 있는 것들을 `user_in_genre_dataframe` 변수에서 얻어와 `genre_by_occupation` 변수에 저장한다. 이후 앞선 방법과 동일하게 `array`를 만든 후 출력한다.
    
- **<사용자 직업에 따른 장르별  평균 평점>**
    
    ```python
    # 직업에 따른 장르 별 평균 평점
    
    dic = {}
    
    for job in user_occupation_data['occupation'].values:
        genre_by_occupation = user_in_genre_dataframe[user_in_genre_dataframe['occupation'] == job]
        
        for g in movie_genre['genre'].values:
            dic[g] = genre_by_occupation[genre_by_occupation[g] == 1]['rating'].mean()
        
        temp = pd.Series(dic).sort_values(ascending=False)
    
    arr1 = np.array([])
    arr2 = np.array([])
    
    for n in temp.index:
        arr1 = np.append(arr1, n)
    
    for n in temp.values:
        arr2 = np.append(arr2, n)
    
    dic={'genre' : arr1, 'average rating' : arr2}
    
    result = pd.DataFrame(dic, index=range(1, 20))
    result.index.name='rank by occupation'
    
    result
    ```
    
    - `mean()` 함수를 사용한다.