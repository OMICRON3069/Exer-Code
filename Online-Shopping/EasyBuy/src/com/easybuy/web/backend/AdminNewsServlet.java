package com.easybuy.web.backend;


import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.easybuy.biz.NewsBiz;
import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.impl.NewsBizImpl;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.entity.News;
import com.easybuy.param.NewsParams;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.web.AbstractServlet;

@WebServlet(urlPatterns = {"/admin/news"}, name = "adminNews")
public class AdminNewsServlet extends AbstractServlet {

    private NewsBiz newsBiz;
    private ProductBiz productBiz;

    public void init() throws ServletException {
        this.newsBiz = new NewsBizImpl();
        this.productBiz = new ProductBizImpl();
    }

    @Override
    public Class getServletClass() {
        return AdminNewsServlet.class;
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String queryNewsList(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 10 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int total = newsBiz.queryNewsCount(new NewsParams());
        Pager pager = new Pager(total, rowPerPage, currentPage);
        pager.setUrl("/admin/news?action=queryNewsList");
        NewsParams params = new NewsParams();
        params.openPage((pager.getCurrentPage() - 1) * pager.getRowPerpage(), pager.getRowPerpage());
        List<News> newsList = newsBiz.queryNewsList(params);
        request.setAttribute("newsList", newsList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 7);
        return "/backend/news/newsList";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String newsDeatil(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        News news = newsBiz.getNewsById(id);
        request.setAttribute("news", news);
        request.setAttribute("menu", 7);
        return "/backend/news/newsDetail";
    }

}
