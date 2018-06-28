package com.easybuy.util;

import java.util.Collection;
import java.util.Map;

public class EmptyUtils {
    public static boolean isEmpty(Object obj) {
        if (obj == null) { // if obj is null
            return true;
        }

        if (obj instanceof CharSequence) { //if obj belongs to CharSequence
            return ((CharSequence)obj).length() == 0;
        }

        if (obj instanceof Collection) { // if obj is empty Collection set
            return ((Collection)obj).isEmpty();
        }

        if (obj instanceof Map) { // if obj is empty Map set
            return ((Map)obj).isEmpty();
        }

        if (obj instanceof Object[]) { // if obj is empty array

            Object[] objects = (Object[]) obj; //convert obj to array

            if (objects.length == 0) {
                return true;
            }

            // if array not empty, but the elements of this array has empty value
            boolean empty = true;
            for (Object object : objects) {
                if (!isEmpty(object)) {
                    empty = false;
                    break;
                }
            }
            return empty;
        }

        return false;

    }

    public static boolean isNotEmpty(Object obj) {
        return !isEmpty(obj);
    }

    private boolean validPropertyEmpty(Object...args) {
        for (Object obj: args) {
            if (EmptyUtils.isEmpty(obj)) {
                return true;
            }
        }
        return false;
    }
}
