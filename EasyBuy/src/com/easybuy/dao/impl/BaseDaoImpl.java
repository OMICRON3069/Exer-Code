package com.easybuy.dao.impl;

import java.sql.*;

public abstract class BaseDaoImpl {
    protected Connection connection;

    protected PreparedStatement pstm;

    public BaseDaoImpl(Connection connection) {
        this.connection = connection;
    }

    public ResultSet executeQuery(String sql,Object[] params) {
        ResultSet rs=null;

        try {
            pstm = connection.prepareStatement(sql);

            if (params != null) {
                for (int i = 0; i < params.length ; i++) {
                    pstm.setObject(i+1,params[i]);
                }
            }

            rs = pstm.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }


        return rs;
    }

    public int executeUpdate(String sql, Object[] params) {
        int updateRows = 0;

        try {
            pstm = connection.prepareStatement(sql);

            for (int i = 0; i<params.length;i++) {
                pstm.setObject(i+1,params[i]);
            }

            updateRows = pstm.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return updateRows;
    }

    public int executeInsert(String sql, Object[] params) {
        Long id = 0L;

        try {
            pstm = connection.prepareStatement(sql,Statement.RETURN_GENERATED_KEYS);

            for (int i = 0; i< params.length ; i++) {
                pstm.setObject(i+1,params[i]);
            }

            pstm.executeUpdate();

            ResultSet rs = pstm.getGeneratedKeys();
            //if rs exist
            if (rs.next()) {
                id = rs.getLong(1);
                System.out.println("The primary key of data is: " + id);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }


        return id.intValue();
    }

    public boolean closeResource() {
        if (pstm != null) {
            try {
                pstm.close();
            } catch (SQLException e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }

    public boolean closeResource(ResultSet rs) {
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }

    public abstract Object table2Class(ResultSet rs) throws Exception;


}
