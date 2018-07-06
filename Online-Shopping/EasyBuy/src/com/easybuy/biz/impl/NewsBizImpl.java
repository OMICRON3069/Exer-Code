package com.easybuy.biz.impl;

import com.easybuy.biz.NewsBiz;
import com.easybuy.dao.NewsDao;
import com.easybuy.dao.impl.NewsDaoImpl;
import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;
import com.easybuy.util.DataSourceUtil;

import java.sql.Connection;
import java.util.List;

public class NewsBizImpl implements NewsBiz {
    @Override
    public void addNews(News news) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            dao.add(news);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public void updateNews(News news) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            dao.update(news);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public void deleteNews(String parameter) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            dao.deleteById(Integer.parseInt(parameter));
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public News getNewsById(String parameter) {
        Connection connection = null;

        News news = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            news = dao.getNewsById(Integer.parseInt(parameter));
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return news;
    }

    @Override
    public List<News> queryNewsList(NewsParams params) {
        Connection connection = null;

        List<News> newsList = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            newsList = dao.queryNewsList(params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return newsList;
    }

    public List<News> queryNewsPageList(NewsParams params) {
        Connection connection = null;

        List<News> newsList = null;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            newsList = dao.queryNewsList(params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return newsList;
    }

    @Override
    public Integer queryNewsCount(NewsParams params) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();

            NewsDao dao = new NewsDaoImpl(connection);
            cc= dao.queryNewsCount(params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc;
    }
}
