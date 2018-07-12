package com.easybuy.web.backend;

import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.easybuy.biz.OrderBiz;
import com.easybuy.biz.impl.OrderBizImpl;
import com.easybuy.entity.Order;
import com.easybuy.entity.OrderDetail;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.web.AbstractServlet;

@WebServlet(urlPatterns = {"/admin/order"}, name = "order")
public class AdminOrderServlet extends AbstractServlet {

    private OrderBiz orderBiz;

    public void init() throws ServletException {
        orderBiz = new OrderBizImpl();
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String userId = request.getParameter("userId");
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 5 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int total = orderBiz.count(Integer.valueOf(userId));
        Pager pager = new Pager(total, rowPerPage, currentPage);
        pager.setUrl("/admin/order?action=index&userId=" + userId);
        List<Order> orderList = orderBiz.getOrderList(Integer.valueOf(userId), currentPage, rowPerPage);
        request.setAttribute("orderList", orderList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 1);
        return "/backend/order/orderList";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String queryOrderDeatil(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String orderId = request.getParameter("orderId");
        List<OrderDetail> orderDetailList = orderBiz.getOrderDetailList(Integer.valueOf(orderId));
        request.setAttribute("orderDetailList", orderDetailList);
        request.setAttribute("menu", 1);
        return "/backend/order/orderDetailList";
    }

    public String queryAllOrder(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 5 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int total = orderBiz.count(null);
        Pager pager = new Pager(total, rowPerPage, currentPage);
        pager.setUrl("/admin/order?action=queryAllOrder");
        List<Order> orderList = orderBiz.getOrderList(null, currentPage, rowPerPage);
        request.setAttribute("orderList", orderList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 9);
        return "/backend/order/orderList";
    }

    @Override
    public Class getServletClass() {
        return AdminOrderServlet.class;
    }
}
