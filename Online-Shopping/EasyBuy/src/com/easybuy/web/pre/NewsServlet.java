package com.easybuy.web.pre;

import com.easybuy.biz.NewsBiz;
import com.easybuy.biz.impl.NewsBizImpl;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


@WebServlet(urlPatterns = {"/News"}, name = "News")
public class NewsServlet extends AbstractServlet {


    private NewsBiz newsBiz;

    @Override
    public void init() throws ServletException {
        newsBiz = new NewsBizImpl();
    }

    @Override
    public Class getServletClass() {
        return NewsServlet.class;
    }

    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return "/pre/newsList";
    }
}
