Welcome to a low-power nuclear reactor controller's documentation!
===================================

**The controller** is intended for the system consisting of a low-power nuclear reactor used over the resistance of components and plants to high doses of radiation. At the center of the reactor are fuel rods alternating with control rods that can be retracted and extended to achieve the desired power level. A M1 motor along with a G gearbox is used to advance and retract the control rods. The entire reactor is housed in a coolant (water) tank, which is thought to remove excess heat from the system. The water flow is controlled by external devices, not shown in the figure. If it is necessary to increase the flow of coolant, it is possible to use a centrifugal pump driven by motor M2. To ensure adequate temperature in the reactor block, it is possible to cool the rooms using a blower driven by motor M3. 

The system includes three temperature sensors:
   * T1 measuring the temperature inside the reactor
   * T2 measuring the temperature of the coolant
   * T3 measuring the temperature in the reactor rooms.

The proper work of the system is supervised by the controller, which constantly monitors the temperature from all sensors and takes appropriate actions if the threshold values are exceeded:
   * If temperature T1 exceeds t_1_e, control rods are inserted (M1 motor is switched on)
   * If the temperature T2 exceeds t_2_e, the M2 motor is switched on
   * If the temperature T3 exceeds t_3_e, the M3 motor is switched on. 

Check out the :doc:`usage` section for further information, including
how to :ref:`installation` the project.

.. note::

   This project is under active development.

Contents
--------

.. toctree::

   usage
