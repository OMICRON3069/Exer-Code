package com.easybuy.util;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

/**
 * the Class which is used to connect database.
 */
public class DataSourceUtil {

    private static String url;
    private static String driver;
    private static String username;
    private static String password;

    static {
        init();
    }

    private static void init () {
        Properties paramas = new Properties();
        String configFile = "database.properties";

        InputStream IS = DataSourceUtil.class.getClassLoader().getResourceAsStream(configFile);
        try {
            paramas.load(IS);
        } catch (IOException e) {
            e.printStackTrace();
        }

        url      = paramas.getProperty("url");
        driver   = paramas.getProperty("driver");
        username = paramas.getProperty("username");
        password = paramas.getProperty("password");


    }

    public static Connection openConnection(){
        try {
            Class.forName(driver);

            return DriverManager.getConnection(url,username,password);

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void closeConnection(Connection connection){
        //test if connection is null
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args){
        if (openConnection() != null) {
            System.out.println("Connected");
        }
        else {
            System.out.println("Connection failed");
        }
    }
}
