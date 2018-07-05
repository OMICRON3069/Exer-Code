package com.easybuy.biz;

import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;

import java.util.List;

public interface NewsBiz {
    void addNews (News news) ;

    void updateNews(News news) ;

    void deleteNews(String parameter) ;

    News getNewsById(String parameter) ;

    List<News> queryNewsList(NewsParams params) ;

    Integer queryNewsCount(NewsParams params) ;
}
