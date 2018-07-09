package com.easybuy.biz.impl;

import com.easybuy.biz.UserBiz;
import com.easybuy.dao.UserDao;
import com.easybuy.dao.impl.UserDaoImpl;
import com.easybuy.entity.User;
import com.easybuy.util.DataSourceUtil;

import java.sql.Connection;
import java.util.List;

public class UserBizImpl implements UserBiz {
    @Override
    public boolean add(User user) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            cc = dao.add(user);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public boolean update(User user) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            cc = dao.update(user);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public boolean deleteUserById(Integer id) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            cc = dao.deleteUserById(id + "");
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public Integer count() {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            cc = dao.count();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc;
    }

    @Override
    public List<User> getUserList(Integer currentPageNo, Integer pageSize) {
        Connection connection = null;

        List<User> userList = null;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            userList = dao.getUserList(currentPageNo, pageSize);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return userList;
    }

    @Override
    public User getUser(Integer id, String loginName) {
        Connection connection = null;

        User user = null;

        try {
            connection = DataSourceUtil.openConnection();
            UserDao dao = new UserDaoImpl(connection);
            user = dao.getUser(id, loginName);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return user;
    }
}
