package com.easybuy.biz;

import com.easybuy.entity.User;

import java.util.List;

public interface UserBiz {
    boolean add(User user);

    boolean update(User user);

    boolean deleteUserById(Integer id);

    Integer count();

    List<User> getUserList(Integer currentPageNo, Integer pageSize);

    User getUser(Integer id, String loginName);
}
