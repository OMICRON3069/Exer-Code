package com.easybuy.dao;

import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;

import java.util.List;

public interface NewsDao {

    void add (News news) throws Exception;

    void update(News news) throws Exception;

    void deleteById(Integer id) throws Exception;

    News getNewsById(Integer id) throws Exception;

    List<News> queryNewsList(NewsParams params) throws Exception;

    Integer queryNewsCount(NewsParams params) throws Exception;


}
