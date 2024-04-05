#include "can_node_base.h"
#include "Vanttec_CANLib/CANMessage.h"
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include "sdv_msgs/srv/uint8.hpp"
#include "std_srvs/srv/empty.hpp"
#include <algorithm>
#include <chrono>

using namespace std::chrono_literals;

class CanNodeUUV : public CanNodeBase {
public:
    CanNodeSDV() : CanNodeBase("uuv_can_node"){
        using namespace std::placeholders;

        // [joystick] -> [this node] -> [stepper pcb] -> [stepper motor]
        // [this node][motor_angle_sub] : convert FLoat64 to CANMessage and send it
        right_motor_sub = this->create_subscription<std_msgs::msg::Float64>(
            "/uuv/right_motor/teleop", 10, [this](const std_msgs::msg::Float64::SharedPtr msg){
                vanttec::CANMessage can_msg;
                vanttec::packFloat(can_msg, 0x15, msg->data);
                send_frame(0x410, can_msg);
            }
        );

    }
protected:
    void parse_frame(const struct can_frame &frame) override {
        vanttec::CANMessage msg;
        std::copy(std::begin(frame.data), std::end(frame.data), std::begin(msg.data));
        msg.len = frame.can_dlc;
        uint8_t vttec_msg_id = vanttec::getId(msg);
        uint32_t can_id = frame.can_id;
        
        auto steady_clock = rclcpp::Clock();

        // RCLCPP_INFO(this->get_logger(), "Got message from: %#X  with vttec id: %#X", can_id, vttec_msg_id);

        if(can_id == 0x407){
            if(vttec_msg_id == 0x03){
                std_msgs::msg::Float64 encoder_msg;
                encoder_msg.data  = vanttec::getFloat(msg);
                auto steady_clock = rclcpp::Clock();
                // RCLCPP_WARN_THROTTLE(this->get_logger(), steady_clock, 1000, "Got encoder message: %f", encoder_msg.data);
                steering_angle_pub->publish(encoder_msg);
            }
        }
    }

    
private:
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr motor_angle_sub;
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanNodeSDV>());
  rclcpp::shutdown();
  return 0;
}
