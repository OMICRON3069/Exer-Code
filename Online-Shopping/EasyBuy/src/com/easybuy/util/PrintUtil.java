package com.easybuy.util;

import com.alibaba.fastjson.JSONObject;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class PrintUtil {
    public static void write(Object result, HttpServletResponse resp) {
        resp.setContentType("text/html;charset=utf-8");

        String json = JSONObject.toJSONString(result);

        print(json, resp);
    }

    private static void print(String json, HttpServletResponse resp) {
        PrintWriter writer = null;
        try {
            if (resp != null) {
                writer = resp.getWriter();
                writer.print(json);
                writer.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            writer.close();
        }
    }
}
