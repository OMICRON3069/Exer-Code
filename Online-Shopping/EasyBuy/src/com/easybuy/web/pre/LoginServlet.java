package com.easybuy.web.pre;

import com.easybuy.biz.UserBiz;
import com.easybuy.biz.impl.UserBizImpl;
import com.easybuy.entity.User;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.ReturnResult;
import com.easybuy.web.AbstractServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = {"/Login"}, name = "Login")

public class LoginServlet extends AbstractServlet {
    private UserBiz userBiz;

    @Override
    public void init() throws ServletException {
        userBiz = new UserBizImpl();
    }

    @Override
    public Class getServletClass() {
        return LoginServlet.class;
    }

    public String toLogin(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return "/pre/login";
    }

    public ReturnResult login(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult returnResult = new ReturnResult();

        String loginName = request.getParameter("loginName");
        String password = request.getParameter("password");
        User user = userBiz.getUser(null, loginName);

        if (EmptyUtils.isEmpty(user)) {
            returnResult.returnFail("User not found");
        } else {
            if (user.getPassword().equals(password)) {
                request.getSession().setAttribute("loginUser", user);
                returnResult.returnSuccess("Login Success");
            } else {
                returnResult.returnFail("Password doesn't match");
            }
        }

        return returnResult;
    }

    public String loginOut(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();

        try {
            User user = (User) request.getSession().getAttribute("loginUser");
            request.getSession().removeAttribute("cart");
            request.getSession().removeAttribute("loginUser");
            request.getSession().removeAttribute("cart2");
        } catch (Exception e) {
            e.printStackTrace();
        }

        result.returnSuccess("Logout success");
        return "/pre/login";

    }
}
