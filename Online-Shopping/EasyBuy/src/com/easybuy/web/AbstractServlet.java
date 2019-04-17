package com.easybuy.web;


import com.easybuy.util.EmptyUtils;
import com.easybuy.util.PrintUtil;
import com.easybuy.util.ReturnResult;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public abstract class AbstractServlet extends HttpServlet {
    public abstract Class getServletClass();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String actionIndicator = req.getParameter("action");

        Method method = null;
        Object result = null;

        try {
            if (EmptyUtils.isEmpty(actionIndicator)) {
                result = execute(req, resp);
            } else {
                method = getServletClass().getDeclaredMethod(actionIndicator, HttpServletRequest.class, HttpServletResponse.class);

                result = method.invoke(this, req, resp);


            }

            toView(req, resp, result);
        } catch (NoSuchMethodException e) {
            String viewName = "404.jsp";
            req.getRequestDispatcher(viewName).forward(req, resp);
        } catch (Exception e) {
            e.printStackTrace();
            if (EmptyUtils.isNotEmpty(result)) {
                if (result instanceof String) {
                    String viewName = "500.jsp";
                    req.getRequestDispatcher(viewName).forward(req, resp);
                } else {
                    ReturnResult returnResult = new ReturnResult();
                    returnResult.returnFail("System fail");
                    PrintUtil.write(returnResult, resp);
                }
            } else {
                String viewName = "500.jsp";
                req.getRequestDispatcher(viewName).forward(req, resp);
            }
        } finally {
        }


    }

    protected void toView(HttpServletRequest req, HttpServletResponse resp, Object result) throws ServletException, IOException {
        if (EmptyUtils.isNotEmpty(result)) {
            if (result instanceof String) {
                String viewName = result.toString() + ".jsp";

                req.getRequestDispatcher(viewName).forward(req, resp);
            } else {
                PrintUtil.write(result, resp);
            }
        }
    }

    public Object execute(HttpServletRequest req, HttpServletResponse resp) {
        return "pre/index";
    }


}
