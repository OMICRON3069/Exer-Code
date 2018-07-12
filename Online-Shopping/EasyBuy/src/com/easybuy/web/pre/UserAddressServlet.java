package com.easybuy.web.pre;

import com.easybuy.biz.UserAddressBiz;
import com.easybuy.biz.impl.UserAddressBizImpl;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;


public class UserAddressServlet extends AbstractServlet {

    private UserAddressBiz userAddressBiz;

    @Override
    public void init() throws ServletException {
        userAddressBiz = new UserAddressBizImpl();
    }

    @Override
    public Class getServletClass() {
        return UserAddressServlet.class;
    }



}
