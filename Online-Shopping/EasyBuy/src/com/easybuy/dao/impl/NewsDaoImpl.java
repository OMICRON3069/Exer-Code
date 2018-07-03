package com.easybuy.dao.impl;

import com.easybuy.dao.NewsDao;
import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class NewsDaoImpl extends BaseDaoImpl implements NewsDao {
    public NewsDaoImpl(Connection connection) {
        super(connection);
    }

    public static void main(String[] args) {
        NewsDaoImpl daoImpl = new NewsDaoImpl(DataSourceUtil.openConnection());


        try {
            NewsParams pp = new NewsParams();
            List<News> jibai =  daoImpl.queryNewsList(pp);
            for (News ji: jibai) {
                System.out.println(ji.getTitle() + "  " + ji.getContent());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void add(News news) throws Exception {
        String sql = " insert into easybuy_news(title, content, createTime ) values(?,?,?) ";

        Object[] params = { news.getTitle(), news.getContent(), new Date()};

        this.executeUpdate(sql,params);
    }

    @Override
    public void update(News news) throws Exception {
        String sql = " update easybuy_news set title = ?, content = ? where id = ? ";

        Object[] params = { news.getTitle(), news.getContent(), news.getId()};

        this.executeUpdate(sql,params);
    }

    @Override
    public void deleteById(Integer id) throws Exception {
        String sql = " delete from easybuy_news where id = ? ";

        Object[] params = { id };

        this.executeUpdate(sql,params);
    }

    @Override
    public News getNewsById(Integer id) {
        News news = new News();

        String sql = " select id, title, content, createTime from easybuy_news where id = ? ";

        Object[] params ={ id };

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql, params);

            while (resultSet.next()) {
                news = table2Class(resultSet);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }


        return news;
    }

    @Override
    public List<News> queryNewsList(NewsParams params) throws Exception {

        List<News> newsList = new ArrayList<News>();

        StringBuffer sql = new StringBuffer(" select * from easybuy_news where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(params.getTitle())) {
            sql.append(" and title like ? ");
            paramList.add(params.getTitle());
        }

        if (EmptyUtils.isNotEmpty(params.getSort())) {
            sql.append(" order by " + params.getSort() + " ");

        }

        if (params.isPage()) {
            sql.append(" limit " + params.getStartIndex() + " , " + params.getPageSize() + "  ");
        }

        ResultSet resultSet = null;
        try {
            resultSet = this.executeQuery(sql.toString(),paramList.toArray());

            while (resultSet.next()) {
                News news = this.table2Class(resultSet);
                newsList.add(news);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return newsList;
    }

    @Override
    public Integer queryNewsCount(NewsParams params) {
        Integer count = 0;

        StringBuffer sql = new StringBuffer(" select * from easybuy_news where 1=1 ");

        List<Object> paramsList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(params.getTitle())) {
            sql.append(" and title like ? ");
            paramsList.add(params.getTitle());
        }
        ResultSet rs = null;

        try {
            rs = this.executeQuery(sql.toString(),paramsList.toArray());

            while (rs.next()) {
                count = rs.getRow();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(rs);
        }


        return count;
    }

    @Override
    public News table2Class(ResultSet rs) throws Exception {
        News news = new News();

        news.setId(rs.getInt("id"));
        news.setTitle(rs.getString("title"));
        news.setContent(rs.getString("content"));
        news.setCreateTime(rs.getDate("createTime"));

        return news;
    }


}
