package com.easybuy.dao;

import com.easybuy.entity.User;

import java.util.List;

public interface UserDao {
    int add (User user) throws Exception;

    int update (User user) throws Exception;

    int deleteUserById (String id) throws Exception;

    Integer count() throws Exception;

    List<User> getUserList(Integer currentPageNo, Integer pageSize) throws Exception;

    User getUser(Integer id, String loginName) throws Exception;
}
