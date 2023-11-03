        cout << "upper eye        : " << eye_width(data, 0, data.size()).index_count * 10 << endl;
        cout << "upper eye x start: " << x_axis.at(eye_width(data, 0, data.size()).x_start_index) << endl;
        cout << "upper eye x end  : " << x_axis.at(eye_width(data, 0, data.size()).x_end_index) << endl;
        cout << "upper eye y axis : " << y_axis.at(eye_width(data, 0, data.size()).y_axis_index) << endl;
        cout << "lower eye        : " << eye_width(data, data.size() - 1, 0).index_count * 10 << endl;
        cout << "lower eye x start: " << x_axis.at(eye_width(data, data.size() - 1, 0).x_start_index) << endl;
        cout << "lower eye x end  : " << x_axis.at(eye_width(data, data.size() - 1, 0).x_end_index) << endl;
        cout << "lower eye y axis : " << y_axis.at(eye_width(data, data.size() - 1, 0).y_axis_index) << endl;