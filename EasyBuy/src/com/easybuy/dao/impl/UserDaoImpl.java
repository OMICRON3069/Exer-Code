package com.easybuy.dao.impl;

import com.easybuy.dao.UserDao;
import com.easybuy.entity.User;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.Pager;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class UserDaoImpl extends BaseDaoImpl implements UserDao {

    public UserDaoImpl(Connection connection) {
        super(connection);
    }


    /**
     *
     * @param user The user to be added
     */
    @Override
    public int add(User user) {

        Integer id = 0;

        try {
            String sql = " insert into easybuy_user" +
                    "(loginName,userName,password,sex,identityCode,email,mobile) " +
                    "values(?,?,?,?,?,?,?) ";

            Object[] params = {user.getLoginName(),user.getUserName(),user.getPassword(),
                    user.getSex(),user.getIdentityCode(),user.getEmail(),user.getMobile()};

            id = this.executeInsert(sql,params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return id;
    }

    public static void main(String[] args) {
        UserDaoImpl daoImpl = new UserDaoImpl(DataSourceUtil.openConnection());
        List<User> userList = daoImpl.getUserList(1, 2);
        for (User user: userList) {
            System.out.println(user.getLoginName()+" "+user.getPassword());
        }
    }


    /**
     *
     * @param user update user info
     */
    @Override
    public int update(User user) {

        Integer count = 0;

        String sql = " update easybuy_user set loginName = ?, userName = ?, type = ?, sex = ?," +
                "identityCode = ?, email = ?, mobile = ? where id = ?";

        try {
            Object[] params={user.getLoginName(),user.getUserName(),user.getType(),
                    user.getSex(),user.getIdentityCode(),
                    user.getEmail(),user.getMobile(),user.getId()};

            count = this.executeUpdate(sql,params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return count;
    }

    @Override
    public int deleteUserById(String id) {

        Integer count = 0;

        try {
            String sql = " delete from easybuy_user where id = ? ";

            Object[] params = { id };

            count = this.executeUpdate(sql,params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return count;
    }

    @Override
    public Integer count() {
        Integer cunt = 0;

        String sql = " select * from easybuy_user ";

        ResultSet rs = null;

        try {
            rs = this.executeQuery(sql, null);

            while (rs.next()) {
                //cunt = rs.getInt("count");
                cunt = rs.getRow();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(rs);
        }

        return cunt;
    }

    @Override
    public List<User> getUserList(Integer currentPageNo, Integer pageSize) {

        List<User> UserList = new ArrayList<User>();

        String sql = " select id, loginName, password, username, sex, " +
                "identityCode, email, mobile, type from easybuy_user limit ?,?";
        ResultSet rs = null;

        try {
            int total = count();

            Pager page = new Pager(total, pageSize, currentPageNo);

            Object[] params = { (page.getCurrentPage()-1)*page.getRowPerpage(), page.getRowPerpage() };

            rs = this.executeQuery(sql,params);

            while (rs.next()) {
                User user = this.table2Class(rs);
                UserList.add(user);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource(rs);
            this.closeResource();
        }

        return UserList;
    }

    @Override
    public User getUser(Integer id, String loginName) throws Exception {
        return null;
    }


    /**
     *
     * @param rs ResultSet of SQL query
     * @return User : User class
     */
    @Override
    public User table2Class(ResultSet rs) throws Exception {

        User user = new User();

        user.setLoginName(rs.getString("loginName"));
        user.setUserName(rs.getString("userName"));
        user.setPassword(rs.getString("password"));
        user.setSex(rs.getInt("Sex"));
        user.setIdentityCode(rs.getString("identityCode"));
        user.setEmail(rs.getString("email"));
        user.setMobile(rs.getString("mobile"));
        user.setType(rs.getInt("type"));
        user.setId(rs.getInt("id"));

        return user;
    }
}
